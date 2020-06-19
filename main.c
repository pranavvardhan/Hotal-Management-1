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
int a =0;
float rate=0;


void
rinsert ()
{
  int n;
  printf ("enter the no. of rooms to be added\n");
  scanf ("%d", &n);
  struct hreserve t;
  FILE *fp;
  fp = fopen ("Rooms.bin", "ab");
  for (int i = 0; i < n; i++)
    {
      printf ("Room\n");
      scanf ("%d", &t.roomno);
      printf ("room type\n");
      scanf("%d",&t.rtype);
      t.check = 0;
      t.status = 'y';
      fwrite(&t, sizeof (struct hreserve), 1, fp);
      a++;
    }
  fclose (fp);
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
  printf ("enter the new password:\n");
  printf(" for better safety include atleast 1uppercase letter 1 symbol and 1number in your password\n");
  FILE *fp;
  fp=fopen("password.txt","w");
  scanf("%s",&npwd);
  printf("enter your password again\n");
  scanf("%s",&gpwd);
  if(strcmp(npwd,gpwd)==0)
  {
  fprintf(fp,"%s",npwd);
  }
  else
  {
      printf("enter matching password\n");
  }
  fclose(fp);
  printf ("the password is changed\n");
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
            printf("Do you want to service room%d\n",t.roomno);
            printf("press 1 for yes\t 2 for no\n");
            scanf("%d",&ans);
            if(ans==1)
            {
                fseek(fp,-1*sizeof(struct hreserve),SEEK_CUR);
                t.check=0;
                printf("room %d has serviced\n",t.roomno);
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
    printf("enter the room no\n");
    scanf("%d",&rno1);
  for(int i=0;i<a;i++)
  {
      fread(&t,sizeof(struct hreserve),1,fp);
      if(t.roomno==rno1)
      {
      printf("room no:%d\nroom type:%d\nstatus:%c\nid:%d\n",t.roomno,t.rtype,t.status,t.id);
      break;
      }
  }
  fclose(fp);
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
         printf("password is incorrect\n");
         fclose(fp);
         return 0;
     }
 }
fclose(fp);

  char ctn = 'y';
  while (ctn == 'y')
    {
      int p;
      printf ("1 for insert\n2 for changing password\n3 for service\n4 for viewing\n 5 for stored contents\n");
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
	    /* dstore();*/
	     return 0;
	 }
	  printf ("do you want to continue\n y to continue n to stop\n");
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
	  printf ("room no :%d\nroom type:%d\n", t.roomno, t.rtype);
	  p = t.roomno;
	  flag = 1;
	  break;
	}}
      fclose (fp);
      if (flag == 0)
	{
	  printf ("rooms are currently not available\n ");
	  return 0;
	}
    
  int reg;
  printf ("do you want book this room\n press 1 for yes press 2 for no\n");
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
	      fwrite (&t, sizeof (struct hreserve), 1, fp);
	      printf ("room booked successfully\n");
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
  float amount;
  if (type == 1)
    {
      amount = 100 * t;
    }
  else if (type==2)
    {
      amount = 200 * t;
    }
  else if (type == 3)
    {
      amount = 500 * t;
    }
  else
    {
      printf ("enter a valid type\n");
      return 0;
    }
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
	  printf ("thankyou\n");
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
   
    printf ("for checkin press 1\nfor checkout press 2\n");
   scanf ("%d", &i);
    if (i == 1)
    {
	   printf ("enter the choice of room\n1 for 1bed\n2 for 2bed\n3 for villa\n");
	   scanf("%d",&type);
	   

     	dno = roomcheck (type);
        if (dno != 0)
	    {
	      int tm;
	      printf ("enter the time of your stay in hours ");
	      scanf ("%d", &tm);
	      amount = amountcalc (tm, type);
	      printf ("your estimated total amount is:\n");
	      printf ("%f", amount);
          return 0;
	    }
    }
    else if (i == 2)
    {
	printf ("enter your room no\n");
	int rno;
	scanf ("%d", &rno);
	checkout (rno);
	printf ("please visit again\n");
    }
  return 0;
}

int
main ()
{
  time_t ltime;
  struct tm *local;
  printf("          ********---     ABC HOTEL    ---********\n");
  ltime=time(NULL);
  local=localtime(&ltime);
  printf("                                                   TIME:%d:%d GMT\n",local->tm_hour,local->tm_min);
  printf("                                                   DATE:%d:%d:%d\n",local->tm_mday,local->tm_mon,local->tm_year-100);
  char c;
  FILE *fp,*ptr;
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
  printf ("customer: press c\nadmin: press a\n");
  scanf ("%c", &c);
  if (c == 'a')
    {
      char rpwd[30];
      printf ("enter the password:\n");
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
