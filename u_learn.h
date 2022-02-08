#ifndef U_LEARN
#define U_LEARN
#include"math-motions/math_sandus.h"
//K-Means Clustering

struct dot_data
{

double* coord;
int n;
int label=0;


dot_data(int ni=100)
{
   coord=new double[ni];n=ni;
}
operator ()(int ni)
{
    coord=new double[ni+1];
    n=ni;


}




 dot_data diff(dot_data a)
{

   dot_data c;
   c.coord=new double[min(a.n,n)+1];
   c.n=min(a.n,n);


   for(int i=1;i<=min(a.n,n);i++)
   c.coord[i]=coord[i]-a.coord[i];

   return c;
}


 dot_data add(dot_data a)
{
   dot_data c;
   c.coord=new double[min(a.n,n)+1];
   c.n=min(a.n,n);


   for(int i=1;i<=min(a.n,n);i++)
   c.coord[i]=coord[i]+a.coord[i];

   return c;

}
void divide(double d,int k=0)
{
   if(k==0)
   for(int i=1;i<=n;i++)
   coord[i]=coord[i]/d;

   else
   coord[k]=coord[k]/d;

}








void set_with_number(double k=0)
{
   for(int i=1;i<=n;i++)
    coord[i]=k;

}

dot_data Copy(int k=0)
{
   dot_data res;
   res.n=n;

   res.coord=new double[n+1];

 if(k==-1)
 {
   for(int i=1;i<=n;i++)
   res.coord[i]=coord[i];

 }

else
   {


 for(int i=1;i<=n;i++)
   res.set_with_number(k);

   }
   return res;
}





void set_coord( int ni,dot_data v )
   {
      if(ni<n)
   {

   for(int i=1;i<=ni;i++)
   coord[i]=v.coord[i];
   n=ni;

   }

   else
   {
      coord=new double[ni+1];
        for(int i=1;i<=ni;i++)
   coord[i]=v.coord[i];
   n=ni;

}
}

double& getValue(int i)
{

   return coord[i];

}








void x(double xi)
{

   coord[1]=xi;


}

void y(double yi)
{

   coord[2]=yi;


}

void z(double zi)
{
   coord[3]=zi;

}

double x()
{

   return coord[1];

}

double y()
{
  return coord[2];
}

double z()
{
   return coord[3];

}




 double dist(dot_data a,char*s="euclid")
   {

     return Metric.cataloque(s,coord,a.coord,n);

   }


   void afisare()
   {
         for(int j=1;j<=n;j++)
         cout<<coord[j]<<" ";
         cout<<endl;
   }




  void  set_label(dot_data* v,int m)
   {
      double minim=99999;

      for(int i=1;i<=m;i++)
      {
         //cout<<"labeling:"<<i<<endl;
         double x=dist( v[i] );
          if(x<=minim)
          { minim=x;label=i
          ;}
      }


   }

  int equal(dot_data a)
   {
      int c=1;

   for(int i=1;i<=min(n,a.n);i++)
      if(coord[i]!=a.coord[i])
      c=0;


      return c;

   }









};

struct cluster
{

   dot_data* groups;
   int n,nr_g;
   int max_iter=100;

 cluster(int n2=20)
   {

      groups=new dot_data[n2+1];
  n=n2;

   }
void operator()(int n2=20)
   {

      groups=new dot_data[n2+1];
  n=n2;

   }



void set_nrc(int n2=20)
   {
  for(int i=1;i<=n;i++)
  groups[i](n2);

   }



 dot_data* rand_unique(int n2,int n3,double a,double b)
  {

     dot_data* res=new dot_data[n2+1];



   for(int i=1;i<=n2;i++)
{
   res[i].coord=new double[n3+1];
   res[i].n=n3;


   int c=1;int trys=0;

do{
      trys++;
   c=1;
 for(int j=1;j<=n3;j++)
{
      res[i].coord[j]=randf(a,b);

}

for(int k=1;k<i;k++)
{

    for(int j=1;j<=n3;j++)
{
      if(res[i].coord[j]!=res[k].coord[j])
         c=0;


}


}




}while(c==1 && trys<100);

 }

return res;


  }


 void train(dot_data* v,int dot_nr,int class_nr,int coord_nr,int a=0,int b=20)
  {
     n=class_nr;
     nr_g=coord_nr;


     groups=rand_unique(n,nr_g,0,10);



     int c1=1;
   int iter=0;

     do{






  iter++;
      c1=1;




     for(int i=1;i<=dot_nr;i++)
     {

 //cout<<"i:"<<i<<endl;
      v[i].set_label(groups,n);

     }

     for(int i=1;i<=n;i++)
     {

          dot_data s=groups[i].Copy();

        int k=0;

        for(int j=1;j<=dot_nr;j++)
        if(v[j].label==i)
        {

           s=s.add(v[j]);
           k++;
        }


        if(k!=0)
        {
      s.divide(k);

      cout<<i<<" "<<k<<" "<<max_iter<<endl;
        s.afisare();
         groups[i].afisare();

     if(groups[i].equal(s)==0)
      {c1=0;groups[i].set_coord(n,s)
      ;}

      }


     }

     }while(c1==0 && iter<=max_iter);

  }


int  predict(dot_data a)
  {
   a.set_label(groups,n);
  return a.label;
  }

int*  predict(dot_data* a,int m)
  {

     int* p=new int[m+1];
     for(int i=1;i<=m;i++)
     {
        a[i].set_label(groups,n);
      p[i]=a[i].label;
     }

  return p;
  }




};

void see_labeled(dot_data* p,int n,int k=0)
{


   for(int i=1;i<=n;i++)
   {
      cout<<"dot:"<<i<<endl;
      cout<<"label:"<<p[i].label<<endl;
   if(k!=0)
   {

      cout<<"coord:";
   for(int j=1;j<=p[i].n;j++)
         cout<<p[i].coord[j]<<" ";
         cout<<endl;


   }

   }

}


struct countKNN
{

int lab;
int count=0;
 int verf(int i)
   {

      if(i==lab)
      {
         count++;
         return 1;
      }
        return 0;
   }


   void counter(int k,Llist<countKNN>& KN )
   {
      int c=0;
      for(int i=1;i<=KN.nr;i++)
      if(KN[i].verf(k))
          c=1;

         if(c==0)
         {
            countKNN use;
              use.lab=1;
              use.count=1;
               KN.add(use);

         }
   }



  int maxl( Llist<countKNN> p)
   {
      int ml=0,mc=0;
      for(int i=1;i<=p.nr;i++)
      {
         if(p[i].count>mc)
         {
            mc=p[i].count;
            ml=p[i].lab;
         }
      }

   return ml;

   }


};







int Knear_neighbours(dot_data a,dot_data* b,int n,int k,char* s="euclid")
{
int inv=0;

do{
      inv=0;
   for(int i=1;i<n;i++)
{

      if(a.dist(b[i],s)>a.dist(b[i+1],s))
      {
         dot_data c; c=b[i];
         b[i]=b[i+1];
         b[i+1]=c;
         inv=1;

      }
}
}
   while(inv!=0);


if(k<=n)
   {
      Llist<countKNN> nei;
      countKNN full;
      for(int i=1;i<=k;i++)
        full.counter(b[i].label,nei);

        return full.maxl(nei);

   }
   else
   {
        Llist<countKNN> nei;
      countKNN full;
      for(int i=1;i<=n;i++)
        full.counter(b[i].label,nei);

        return full.maxl(nei);

   }





}

















#endif
















