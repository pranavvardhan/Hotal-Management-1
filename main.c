#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct hreserve
{
  int roomno;
  int rtype;
  int check;
  char status;
  time_t second;
  int id;
};
struct det{
    int droomno;
    char name[20];
    time_t intime,outtime;
    struct tm *l;
};
struct price
{
    float bed_1,bed_2,vil_la;
};
int a =0;
float rate=0;


void
rinsert ()
{
  int n;
  printf ("Enter the no. of rooms to be added\n");
  scanf ("%d", &n);
  struct hreserve t;
  FILE *fp;
  fp = fopen ("Rooms.bin", "ab");
  for (int i = 0; i < n; i++)
    {
      printf ("Enter the Room number:\n");
      scanf ("%d", &t.roomno);
      printf ("Enter the room type:\t <1> for 1bed <2> for 2bed <3> for villa\n");
      scanf("%d",&t.rtype);
      t.check = 0;
      t.status = 'y';
      fwrite(&t, sizeof (struct hreserve), n, fp);
      a++;
    }
  fclose (fp);
  printf("The room is added\n");
  FILE *ptr;
  ptr=fopen("norooms.txt","w");
  if(ptr==NULL)
  {
      printf("error");
      exit(1);
  }
  fprintf(ptr,"%d",a);
  fclose(ptr);
 
   
  
}

void
pwdchange ()
{
  char npwd[10],gpwd[30];
  printf ("Enter the new password:\n");
  printf("For better safety include atleast 1uppercase letter 1 symbol and 1number in your password\n");
  FILE *fp;
  fp=fopen("password.txt","w");
  scanf("%s",&npwd);
  printf("Enter your password again\n");
  scanf("%s",&gpwd);
  if(strcmp(npwd,gpwd)==0)
  {
  fprintf(fp,"%s",npwd);
  }
  else
  {
      printf("Enter matching password\n");
  }
  fclose(fp);
  printf ("The password is changed\n");
}
void rservice()
{
    struct hreserve t;
    FILE *fp;
    int ans;
    fp=fopen("Rooms.bin","rb+");
    for(int i=0;i<a;i++)
    {
        fread (&t, sizeof (struct hreserve), 1, fp);
        if(t.check==1 && t.status== 'y')
        { 
            printf("Do you want to service room number:%d\n",t.roomno);
            printf("Press 1 for yes\t press 2 for no\n");
            scanf("%d",&ans);
            if(ans==1)
            {
                fseek(fp,-1*sizeof(struct hreserve),SEEK_CUR);
                t.check=0;
                printf("Room %d has serviced\n",t.roomno);
                fwrite(&t, sizeof (struct hreserve), 1, fp);
                continue;
            }
            else if(ans==2)
            {
                continue;
            }
        }
    }
    fclose(fp);
}
void view()
{
    struct hreserve t;
    FILE *fp;
    fp=fopen("Rooms.bin","rb");
    int rno1;
    printf("Enter the room no\n");
    scanf("%d",&rno1);
  for(int i=0;i<a;i++)
  {
      fread(&t,sizeof(struct hreserve),1,fp);
      if(t.roomno==rno1)
      {
      printf("Room no:%d\nRoom type:%d\nStatus:%c\nID:%d\n",t.roomno,t.rtype,t.status,t.id);
      break;
      }
  }
  fclose(fp);
}
void priceincrease()
{
    FILE *fp;
    struct price t;
    fp=fopen("price.bin","wb");
    printf("Enter the new amounts for the types \n*1bed\n*2bed\n*villa\n");
    scanf("%f%f%F",&t.bed_1,&t.bed_2,&t.vil_la);
    fwrite(&t,sizeof(struct price),1,fp);
    fclose(fp);
    printf("The new prices are updated");
}

int
admin (char *pwd)
{
 FILE *fp;
 fp=fopen("password.txt","r");
 char ch[20];
 while(fscanf(fp,"%s",ch)!=EOF)
 {
     if(strcmp(ch,pwd)!=0)
     {
         printf("Password is incorrect\n");
         fclose(fp);
         return 0;
     }
 }
fclose(fp);

  char ctn = 'y';
  while (ctn == 'y')
    {
      int p;
      printf("ADMIN MENU:\n");
      printf ("PRESS\n<1> for adding new room\n<2> for changing password\n<3> for servicing room\n<4> for viewing\n<5> for new rents\n");
      scanf ("%d", &p);
      switch (p)
	{
	case 1:
	  {
	    rinsert ();
	    return 0;
	    break;
	    
	  }

	case 2:
	  {
	    pwdchange ();
	    return 0;
	    break;
	  }
	  
	 case 3:
	 {
	     rservice();
	     return 0;
	 }
	 
	 case 4:
	 {
	     view();
	     return 0;
	 }
	 case 5:
	 {
	     priceincrease();
	     return 0;
	 }
	  printf ("Do you want to continue\n y to continue n to stop\n");
	  scanf ("%c", &ctn);

	}
    }
    return 0;

}

int
roomcheck (int type)
{
  int i, flag = 0;
  int p = 0;
  FILE *fp;
  struct hreserve t;
  fp = fopen ("Rooms.bin", "rb+");
  for(i=0;i<a;i++)
    {
      fread (&t, sizeof (struct hreserve), 1, fp);
      
       
      if (t.status == 'y' &&  t.rtype == type)
	{
	  printf ("Room no :%d\nRoom type:%d\n", t.roomno, t.rtype);
	  p = t.roomno;
	  flag = 1;
	  break;
	}}
      fclose (fp);
      if (flag == 0)
	{
	  printf ("Rooms are currently not available\n ");
	  return 0;
	}
    
  int reg;
  printf ("Do you want book this room:\n press 1 for yes press 2 for no\n");
  scanf ("%d", &reg);
  if (reg == 1)
    {

      FILE *fp;
      fp = fopen ("Rooms.bin", "rb+");
      for(i=0;i<a;i++)
	{
	  fread (&t, sizeof (struct hreserve), 1, fp);
	  if (t.status == 'y' &&  t.rtype == type)
	    {
	      fseek(fp,-1*sizeof(struct hreserve),SEEK_CUR);
	      t.status = 'n';
	      t.check = 1;
	      t.id = rand();
	      printf("Your unique ID:%d\n",t.id);
	      fwrite (&t, sizeof (struct hreserve), 1, fp);
	      printf ("Room booked successfully\nUse your ID to check in your visit\n");
	      break;
	    }
	}
	 fclose (fp);
    }if(reg==2)
    {
        return 0;
    }
    
    
 
  return p;

}

float
amountcalc (int t, int type)
{
   FILE *fp;
   float amount;
   struct price p;
   float a=100,b=200,c=500;
   fp=fopen("price.bin","rb");
   if(fp==NULL)
   {
  if (type == 1)
    {
      amount = a * t;
    }
  else if (type==2)
    {
      amount = b * t;
    }
  else if (type == 3)
    {
      amount = c * t;
    }
  else
    {
      printf ("Enter a valid type\n");
      return 0;
    }
  return amount;
   }
   fread(&p,sizeof(struct price),1,fp);
   a=p.bed_1;
   b=p.bed_2;
   c=p.vil_la;
    if (type == 1)
    {
      amount = a * t;
    }
  else if (type==2)
    {
      amount = b * t;
    }
  else if (type == 3)
    {
      amount = c * t;
    }
  else
    {
      printf ("Enter a valid type\n");
      return 0;
    }
    fclose(fp);
    return amount;
}


void
checkout (int drno)
{
  int i;
  FILE *fp;
  fp = fopen ("Rooms.bin", "rb+");
  struct hreserve t;
  for(i=0;i<a;i++)
    {
      fread (&t, sizeof (struct hreserve), 1, fp);
      if (t.roomno == drno)
	{
	  fseek(fp,-1*sizeof(struct hreserve),SEEK_CUR);
	  t.status = 'y';
	  t.id=0;
	  fwrite (&t, sizeof (struct hreserve), 1, fp);
	  printf (" **** THANKYOU ****\n");
	  break;
	}
    }
  fclose (fp);
  printf("Rate us out of 5marks:  -** your ratings are displyed at home screen\n");
  FILE *ptr;
  ptr=fopen("rateus.txt","a");
  int j;
  scanf("%d",&j);
  fprintf(ptr,"%d",j);
  fclose(ptr);
  char sh= ' ';
   ptr=fopen("rateus.txt","a");
   fputc(sh,ptr);
   fclose(fp);
  
}
int customer()
{
    float amount;
  int dno = 0;
  int type;
  char ch[30];
  int i;
   
    printf ("For checkin press 1\nFor checkout press 2\n");
   scanf ("%d", &i);
    if (i == 1)
    {
	   printf ("Enter the choice of room:\n<1> for 1bed\n<2> for 2bed\n<3> for villa\n");
	   scanf("%d",&type);
	   

     	dno = roomcheck (type);
        if (dno != 0)
	    {
	      int tm;
	      printf ("Enter the time of your stay in hours:\n ");
	      scanf ("%d", &tm);
	      amount = amountcalc (tm, type);
	      printf ("Your estimated total amount is:\n");
	      printf ("%f", amount);
          return 0;
	    }
    }
    else if (i == 2)
    {
	printf ("Enter your room no\n");
	int rno;
	scanf ("%d", &rno);
	checkout (rno);
	printf ("*** << Please visit again >> ***\n");
    }
  return 0;
}

int
main ()
{
   FILE *fptr,*fptr1;
  int instruct,flag=1;
  if((fptr=fopen("norooms.txt","r"))==NULL)
  {
     
      printf("* Seems you are using this program for the first time\n\n");
      printf("* Customize this program to your needs\n\n");
      printf("* It takes a while to set up\n\n");
      char name[30];
      printf("Enter the name of your hotel\n");
      scanf("%s",&name);
      fptr1=fopen("hotelname.txt","w");
      fprintf(fptr1,"%s",name);
      fclose(fptr1);
      fptr1=fopen("norooms.txt","w");
      fprintf(fptr1,"%d",flag);
      fclose(fptr1);
      fptr1=fopen("password.txt","w");
      printf("Enter your administrator password\n");
      char pass[30];
      scanf("%s",&pass);
      fprintf(fptr1,"%s",pass);
      fclose(fptr1);
     
      printf("** Your setup is complete **\n");
      exit(5);
 
  }
   fclose(fptr);
  time_t ltime;
  struct tm *local;
   FILE *fp,*ptr;
   fp=fopen("hotelname.txt","r");
   char htl[30];
   fscanf(fp,"%s",htl);
  printf("          ********---     %s    ---********\n",htl);
  fclose(fp);
  ltime=time(NULL);
  local=localtime(&ltime);
  printf("                                                   TIME:%d:%d GMT\n",local->tm_hour,local->tm_min);
  printf("                                                   DATE:%d:%d:%d\n",local->tm_mday,local->tm_mon,local->tm_year-100);
  char c;
  struct hreserve t;
  float sum=0;
  int j,l=0;
  fp=fopen("rateus.txt","r");
  while(fscanf(fp,"%d",&j)!=EOF)
  {
      sum=sum+j;
      l++;
  }
  fclose(fp);
  printf("RATING:%.2f              --your ratings helps us improve\n",sum/l);
  
  ptr=fopen("norooms.txt","r");
  if(ptr==NULL)
  {
      
      exit(1);
  }
  fscanf(ptr,"%d",&a);
  fclose(ptr);
  printf ("TO LOGIN AS CUSTOMER: press c\nTO LOGIN AS ADMIN: press a\n");
  scanf ("%c", &c);
  if (c == 'a')
    {
      char rpwd[30];
      printf ("Enter the admin password:\n");
      scanf("%s",&rpwd);
      
      admin (rpwd);
      return 0;
      
    }
  else if (c == 'c');
  {
    customer();
  }
   
  return 0;
}
