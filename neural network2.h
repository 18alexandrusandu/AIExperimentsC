#ifndef NEURAL NETWORK_H
#define NEURAL NETWORK_H

#include<iostream>
#include<fstream>
#include"math-motions/math_sandus.h"
#include<windows.h>

using namespace std;








template<typename T>
T* convert(T**a,int& n,int& m)
{
T* d;
d=new T[n*m*2];

d[0]=n*m;
for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   d[(i-1)*m+j]=a[i][j];

return d;

}
template<typename T>

int any_ofm(T** a,int n,int m,double er=0.9,int op=1)
{
for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
{

   if(a[i][j]>er && op==1)return 1;
   if(a[i][j]<er && op==2)return 1;
   if(a[i][j]==er && op==3)return 1;

}
return 0;
}


template<typename T>
T** convert2(T*a,int n,int m,int n2=0,int n3=0)
{


if(n2==0)n2=n;
if(n3==0)n3=m;

T** d;
d=new T*[n+5];
for(int i=0;i<=n+3;i++)
d[i]=new T[m+5];

d[1][0]=n2;
d[2][0]=n3;

for(int i=1;i<=n2;i++)
   for(int j=1;j<=n3;j++)

   d[i][j]=a[(i-1)*n3+j];

return d;

}


template<typename T>
void chiller(T** a,int n,int m ,double b=10000,double d=0.00005)
{

for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   {


   if(a[i][j]>b|| (a[i][j]<d && a[i][j]>0) )a[i][j]=0.1;
   if(a[i][j]<-b ||(a[i][j]>-d && a[i][j]<0))a[i][j]=-0.1;
   }

}






struct Layer
{

double learn_rate;

int nr_l;

int nr_c;

double* bias;

double** widt;


double** operator [](char a[])
{
if(strcmp(a,"weigths")==0)return widt;

return 0;

}




double** give_widt(int n,int m,double** f=NULL)
{

widt=new double*[n+2];
for(int i=0;i<=n+1;i++)
 widt[i]=new double[m+1];

if(f!=NULL)
   move_pp(widt,f,n,m);
nr_l=n;
nr_c=m;

return widt;

}
double* give_bias(int n,double* f=NULL)
{
   bias=new double[n+2];
   if(f!=NULL)
   move_d(bias,f,n);
return bias;
}




double** rand_widt(int n,int m,int a=0,int b=1)
{
nr_l=n;
nr_c=m;

widt=new double*[n+2];
for(int i=0;i<=n+1;i++)
 widt[i]=new double[m+1];

for(int i=1;i<=n;i++)
 for(int j=1;j<=m;j++)
 widt[i][j]=randf(a,b);


return widt;

}

double** ZeroW(int n,int m,int a=0)
{
nr_l=n;
nr_c=m;

widt=new double*[n+2];
for(int i=0;i<=n+1;i++)
 widt[i]=new double[m+1];

for(int i=1;i<=n;i++)
 for(int j=1;j<=m;j++)
 widt[i][j]=a;

return widt;

}



double* rand_bias(int n,int a=0,int b=1)
{

bias=new double[n+1];

for(int i=1;i<=n;i++)

 bias[i]=randf(a,b);

return bias;

}

double* ZeroB(int n,int a=0)
{

bias=new double[n+1];

for(int i=1;i<=n;i++)

 bias[i]=a;

return bias;

}











double** forwardn(double* b,int n,int m)
{
double** R;
R=new double*[n+5];
R[0]=new double[m+5];
R[0][0]=m;

for(int i=1;i<=n;i++)
   {
      R[i]=new double[m+5];
      for(int j=1;j<=m;j++)
      R[i][j]=b[(i-1)*m+j]*widt[i][j];
   R[i][0]=m;
   }

return R;

}



void set_weight( int n,int np)
{

nr_l=n;

widt=new double*[n];

bias=new double[n];

for(int i=1;i<n;i++)
   {

widt[i]=new double[np+5];
for(int j=1;j<=np;j++)
widt[i][j]=randf(0,1);

bias[i]=randf(-2,2);

}


}

double brute_sum_widt(double a[],int n)
   {
   double sum=0;
for(int i=1;i<=nr_l;i++)
{
for(int j=1;j<=n;j++)
sum+=widt[i][j]*a[j];

sum+=bias[i];

}
return sum;

}




double* svm(double**a,double b[],int n)
{
   double* sa=new double[(unsigned int)n];

   for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
   sa[i]=a[i][j]*b[j];

}


double* sva(double**a,double b[],int n)
{
   double* sa=new double[n];

   for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
   sa[i]=a[i][j]*b[j];

}

template<typename T>
double** mean_square2(T** a,T** b,int n,int m)
{

double** u=new double*[n+2];

for(int i=0;i<=n;i++)
u[i]=new double[m+2];

for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   u[i][j]=((a[i][j]-b[i][j])*(a[i][j]-b[i][j]))/2;

return u;
}



template<typename T>
double* mean_square(T* a,T* b,int n)
{


double* u=new double[n+2];

for(int i=1;i<=n;i++)

   u[i]=((a[i]-b[i])*(a[i]-b[i]))/2;
   return u;
}

template<typename T>
double TError(T** a,T** b,int n,int m)
{
   double s=0;
double** u=mean_square2(a,b,n,m);
for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
 s+=u[i][j];


return u;
}


template<typename T>
double TError(T* a,T* b,int n)
{
   double s=0;
double* u=mean_square(a,b,n);
for(int i=1;i<=n;i++)
 s+=u[i];
return u;

}




double dC_dal(double y,double a)
{
   return 2*(a-y);

}


double dz_dw(double al_1 ,double z,double w)
{
return al_1;
}






};


double drelu(double x)
{
if(x>0)return 1;

else return 0;
}


double dsigmoid(double x,double p=0)
{
   return Math.sigmoid(x)*(1-Math.sigmoid(x));
}



double arsigmoid(double x,int p=0)
{
   return x*(1-x);
}





template<typename T>
T** convolution(T**mat,T** fiter,int n,int m,int k,int l)
{
T** result=new T*[n+2];
for(int i=0;i<=n+1;i++)
result[i]=new T[m+2];

int wi=0, hi=0;
for(int i=1;i<=n;i++)
{
   if(i+k<=n+1)hi++;
   wi=0;
   for(int j=1;j<=m;j++)
   {
      if(j+l<=m+1)wi++;


      result[hi][wi]=0;

   //receptive field
      for(int h=0;h<k;h++)
      {
      for(int w=0;w<l;w++)
      if(i+h<=n && j+w<=m)
         result[hi][wi]+=fiter[h+1][w+1]*mat[i+h][j+w];
      }
   }
   }

result[1][0]=hi;
result[2][0]=wi;

return result;


}


template<typename T>
T** pooling(T** mat,int n,int m,int k,int l )
{

T** output;


output=new T*[n+2];

for(int i=0;i<=n+2;i++)
   output[i]=new T[m+2];


int wi=0,hi=0;

for(int i=1;i<=n;i++)
{
if(i+k<=n+1)hi++;
 wi=0;
   for(int j=1;j<=m;j++)
   {
    if(j+l<=m+1)wi++;


   T maxi=mat[i][j];

      for(int h=0;h<k;h++)
      {
      for(int w=0;w<l;w++)
      {
         if(i+h<=n && j+w<=m)
         {
       //  cout<<mat[i+h][j+w]<<" ";


        if(mat[i+h][j+w]>=maxi)
        {   maxi=mat[i+h][j+w];
            output[hi][wi]=maxi;
         }
         }

      }
  // cout<<endl;
      }
 //cout<<"output"<<output[hi][wi]<<endl;
   }
   }

output[1][0]=hi;
output[2][0]=wi;

return output;

}


template<typename T>
T** pooling2(T** mat,int n,int m,int k,int l )
{

T** output;

output=new T*[n];

for(int i=0;i<=n+1;i++)
   output[i]=new T[m+1];

int wi=0,hi=0;


for(int i=1;i<=n;i+=k)
{  if(i+k<=n+2)hi++;
   wi=0;
   for(int j=1;j<=m;j+=l)
   {

   if(j+l<=m+2)wi++;


   output[hi][wi]=0;

   //receptive field
   T maxi=mat[i][j];
      for(int h=0;h<k;h++)
      {

      for(int w=0;w<l;w++)
      if(i+h<=n && j+w<=m)
      {
        // cout<<mat[i+h][j+w]<<" ";

        if(mat[i+h][j+w]>=maxi)
        {   maxi=mat[i+h][j+w];
            output[hi][wi]=maxi;

        }


      }


 }
  //cout<<endl<<"output"<<output[hi][wi]<<endl;

   }
}
output[1][0]=hi;
output[2][0]=wi;

return output;

}



template<typename T>
void Retrier(T** a,int n,int m,double prb=1,T b[]={0})
{

double p=randf(0,1);
if(p>=prb)
{

int i=rand()%n;
   for(int j=1;j<=m;j++)
   a[i][j]=0;
 if(b!=0)b[i]=0;
}

;}


template<typename T>
T** Softmax(T** a,int n,int m)
{
   T** res=new T*[n+1];
   for(int i=0;i<=n;i++)
 res[i]=new T[m+1];

T sume=0;
for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   sume+=exp(a[i][j]);

   for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   res[i][j]=exp(a[i][j])/sume;

res[1][0]=n;
res[2][0]=m;


return res;

}


template<typename T>
void rfm(T**a,int n,int m,int s=2)
{

for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   a[i][j]=Math.rf(a[i][j],s);

}







template<typename T>
void rfm(T*a,int n,int s=2)
{
for(int i=1;i<=n;i++)
   a[i]=Math.rf(a[i],s);
}


template<typename T>
void ReLu(  T** a,int n,int m,int u=0)
{
   for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
     {
        if(a[i][j]<=u)a[i][j]=0;

     }
}
template<typename T>
T** reshape(T** image,int ah,int aw,double nh,double nw)

{
T** ni;
ni=new T*[(int)nh+1];
for(int i=0;i<=nh;i++)
ni[i]=new T[(int)nw+1];

double sw=nw/aw;
double sh=nh/ah;

   for(int i=1;i<=nh;i++)
    for(int j=1;j<=nw;j++)
     {
     int p1=(double)i/sh ,p2=(double)j/sw;

if(p1 <=ah && p2<=aw)
      ni[i][j]=image[p1][p2];

     }
   delete[] image;
   return ni;
}


template<typename T>
T** refield(T** a,int ln,int lm,int spx=1,int spy=1)
{
int wi=0,hi=0;

T** result=new T*[ln+2];

for(int i=0;i<=ln+2;i++)

result[i]=new T[lm+2];


for(int i=spx;i<=spx+ln;i++)
for(int j=spy;j<=spy+lm;j++)
result[i-spx][j-spy]=a[i][j];

result[1][0]=ln;
result[2][0]=lm;

return result;

}






template<typename T>
T** conja(T** s,int n,int m,int k,int l)
{

   T**ford=new T*[n+1];

   for(int i=0;i<=n;i++)
   ford[i]=new T[m+1];

   int wi=0,hi=0;

  // cout<<"nu aici"<<endl;

   for(int i=1;i<=n;i++)
   {
   if(i!=k)hi++;wi=0;
   for(int j=1;j<=m;j++)
   {
   if(j!=l)wi++;
      if(i!=k && j!=l)
      ford[hi][wi]=s[i][j];

   }


   }

   ford[1][0]=hi;
   ford[2][0]=wi;

   return ford;

}

/*
template<typename T>
T** inversam(T** f,int n)
{


T** a,**b,**c;

T** inv=new T*[n+1];
for(int i=0;i<=n+1;i++)
inv[i]=new T[n+1];

int  dt=detm(f,n);

if(dt!=0)
{
   a=transp(f,n,n);

for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)
    inv[i][j]=(double)1/detm(a,n)*detm(conja(a,n,n,i,j),n-1);


return inv;
}
cout<<"matrice neinversabila"<<endl;
return 0;


}

*/

template<typename T>
T argmax(T**a,int n,int m)
{
T maxi=a[1][1];
for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   if(a[i][j]>=maxi)maxi=a[i][j];

   return maxi;


}
template<typename T>
T argmax(T*a,int n)
{
T maxi=a[1];
for(int i=1;i<=n;i++)
   if(a[i]>=maxi)maxi=a[i];

   return maxi;

}



template<typename T>
T** Multm(T** b,int n,int m,int k)
{
   T** res;
res=new T*[n+1];
for(int i=0;i<=n;i++)
   res[i]=new T[m+2];

for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
{
res[i][j]=b[i][j]+k;


}
return res;
}

template<typename T>
T** Multma(T** b,int n,int m,T k[])
{
   T** res;
res=new T*[n+1];
for(int i=0;i<=n;i++)
   res[i]=new T[m+2];

for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
{
res[i][j]=b[i][j]*k[i];

}
return res;
}



struct Neural_NetworkSD
{


double lr=0.2;

int drop=0;
double drop_p=0;

int in,hid=0,out,hid2,d=10;

Layer Inp_nodes;

Layer* Hidd;


Layer Out_nodes;

Neural_NetworkSD(int i,int hl,int hn,int o)
{
   in=i;
   Create(o,i,hl,hn);

}

Neural_NetworkSD()
{

}

template<typename T>
   T** predict(T* a,int d=0,T(*f)(T,int)=sigmoid)
{
   return feedforward(a,in,1,d,f);
}




void make_outr(int n,int m,int a,int b)
{

  Out_nodes.widt=Out_nodes.rand_widt(n,m,a,b);
  Out_nodes.bias=Out_nodes.rand_bias(n,a,b);

  Out_nodes.nr_c=m;
  Out_nodes.nr_l=n;


}


void make_out(int n,int m,double**a,double* b)
{

  Out_nodes.widt=Out_nodes.give_widt(n,m,a);
  Out_nodes.bias=Out_nodes.give_bias(n,b);

  Out_nodes.nr_c=m;
  Out_nodes.nr_l=n;

}



void make_hidtr(int t,int n,int m=0,int a=0,int b=1)
{
   hid=t;
   if(m!=0)d=m;
   Hidd=new Layer[t+1];
   for(int i=1;i<=t;i++)
   {

    Hidd[i].widt=Hidd[i].rand_widt(n,d,a,b);
    Hidd[i].bias=Hidd[i].rand_bias(n,a,b);
   Hidd[i].nr_c=d;
   Hidd[i].nr_l=n;

   }

}


void make_hidt(int t,int n,int m,double** a,double b[]={NULL})
{
   hid=t;
   if(m!=0)d=m;
   Hidd=new Layer[t+1];
   for(int i=1;i<=t;i++)
   {

    Hidd[i].widt=Hidd[i].give_widt(n,m,a);
    if(b!=0)
    Hidd[i].bias=Hidd[i].give_bias(n,b);
   Hidd[i].nr_c=m;
   Hidd[i].nr_l=n;
   }

}


void make_hidtr2(int t,int n,int m=0,int a=0,int b=1)
{
   hid=t;
   if(m!=0)d=m;
   Hidd=new Layer[t+1];


   Hidd[1].widt=Hidd[1].rand_widt(n,d,a,b);
   Hidd[1].bias=Hidd[1].rand_bias(n,a,b);
   Hidd[1].nr_c=d;
   Hidd[1].nr_l=n;

   for(int i=2;i<=t;i++)
   {
   Hidd[i].widt=Hidd[i].rand_widt(n,Hidd[i-1].nr_l,a,b);
   Hidd[i].bias=Hidd[i].rand_bias(n,a,b);
   Hidd[i].nr_c=Hidd[i-1].nr_l;
   Hidd[i].nr_l=n;
   }

}



void make_hidt2(int t,int n,int m,double** a,double b[]={NULL})
{
   hid=t;
   if(m!=0)d=m;
   Hidd=new Layer[t+1];

    Hidd[1].widt=Hidd[1].give_widt(n,m,a);
    if(b!=0)
    Hidd[1].bias=Hidd[1].give_bias(n,b);
   Hidd[1].nr_c=m;
   Hidd[1].nr_l=n;



   for(int i=2;i<=t;i++)
   {
 Hidd[i].widt=Hidd[i].give_widt(n,Hidd[i-1].nr_l,a);
    if(b!=0)
    Hidd[i].bias=Hidd[i].give_bias(n,b);
   Hidd[i].nr_c=Hidd[i-1].nr_l;
   Hidd[i].nr_l=n;

   }
}







void make_hid1r(int n,int m=0,int a=0,int b=1)
{
   hid++;
   if(m!=0)d=m;

   Layer* u;
   u=new Layer[hid+1];

   if(hid>1 && Hidd!=0)
   {
      for(int i=0;i<hid;i++)
      u[i]=Hidd[i];

   }

u[hid].widt=u[hid].rand_widt(n,d,a,b);
u[hid].bias=u[hid].rand_bias(n,a,b);
u[hid].nr_l=n;
u[hid].nr_c=d;

Hidd=u;


}

void chillb(Layer b,double p=10000)
{
   for(int i=1;i<=b.nr_l;i++)
   {
   if(b.bias[i]>p)b.bias[i]=0;
    if(b.bias[i]<-p)b.bias[i]=0;
   }
}


void Chiler_network(double p=10000)
{


chiller(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c,p);
chillb(Out_nodes);

   for(int i=1;i<=hid;i++)
   {
chiller(Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c,p);
chillb(Hidd[i]);

}



}

void make_hid12r(int n,int m=0,int a=0,int b=1)
{
   hid++;
   if(m!=0)d=m;
   Layer* u;
   u=new Layer[hid+1];

   if(hid>1 && Hidd!=0)
   {
      for(int i=0;i<hid;i++)
      u[i]=Hidd[i];
   }


u[hid].widt=u[hid].rand_widt(n,u[hid-1].nr_l,a,b);
u[hid].bias=u[hid].rand_bias(n,u[hid-1].nr_l,b);
u[hid].nr_l=n;
u[hid].nr_c=d;

Hidd=u;


}




void make_hid1(int n,int m,double**f,double f2[]={NULL})
{
   hid++;
  // if(m!=0)d=m;


   Layer* u;
   u=new Layer[hid+1];

   if(hid>1 && Hidd!=0)
   {
      for(int i=0;i<hid;i++)
      u[i]=Hidd[i];

   }

 u[hid].widt=u[hid].give_widt(n,m,f);
 if(f2!=NULL)
 u[hid].bias=u[hid].give_bias(n,f2);

u[hid].nr_l=n;
u[hid].nr_c=m;

Hidd=u;
}



void give_gata(Layer a )
{
   Inp_nodes=a;

}






template<typename T>
void give_data(T** a,int n,int m,T*b={NULL})
{
   Inp_nodes.widt=Inp_nodes.give_widt(n,m,a);

   if(b!=NULL)
   Inp_nodes.bias=Inp_nodes.give_bias(b[0],b);
   d=m;


}

Neural_NetworkSD* copynn()
{
   Neural_NetworkSD* t=new Neural_NetworkSD;
   t->Create(out,in,hid,hid2);

 t->in=in;t->hid=hid;t->hid2=hid2;
 t->out=out;

   t->lr=lr;
   t->drop_p=drop_p;
   t->d=d;
   t->drop=drop;

   move_pp(t->Out_nodes.widt,Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c);
   move_sd(t->Out_nodes.bias,Out_nodes.bias,Out_nodes.nr_l);


   for(int i=1;i<=hid2;i++)
   {
   move_pp(t->Hidd[i].widt,Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c);
   move_sd(t->Hidd[i].bias,Hidd[i].bias,Hidd[i].nr_l);
   }

return t;
}
Neural_NetworkSD copynns()
{

   Neural_NetworkSD t;
   t.Create(out,in,hid,hid2);


 t.in=in;t.hid=hid;t.hid2=hid2;
 t.out=out;
 t.lr=lr;
   t.drop_p=drop_p;
   t.d=d;
   t.drop=drop;

   move_pp(t.Out_nodes.widt,Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c);
   move_sd(t.Out_nodes.bias,Out_nodes.bias,Out_nodes.nr_l);


   for(int i=1;i<=hid2;i++)
   {
   move_pp(t.Hidd[i].widt,Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c);
   move_sd(t.Hidd[i].bias,Hidd[i].bias,Hidd[i].nr_l);
   }

return t;
}










void create(Layer in,Layer out,Layer* hidd,int hd)
   {
      Inp_nodes=in;
      Out_nodes=out;
      Hidd=hidd;
      hid=hd;
   }

void Create(int nr_n,int nr_i,int hk,int nr_nh)
   {

   in=nr_i;
   out=nr_n;
   hid2=nr_nh;

      make_hidtr2(hk,nr_nh,nr_i,-10,10);

      Out_nodes.widt=Out_nodes.rand_widt(nr_n,nr_nh,-10,10);

      Out_nodes.bias=Out_nodes.rand_bias(nr_n);

   }

 struct Genetics
 {




 };



   template<typename T,typename R>
T** feedforward(T a[],int n,int m,R d2,T(*f)(T,R)=sigmoid)
{

give_data(convert2(a,n,m),n,m);


T** u=dotppp(Hidd[1].widt,Inp_nodes.widt,Hidd[1].nr_l,Hidd[1].nr_c,Inp_nodes.nr_l,Inp_nodes.nr_c);





int p=1;


if(Hidd[1].bias!=NULL)
add2(u,convert2(Hidd[1].bias,Hidd[1].nr_l,p),Hidd[1].nr_l,p);

mapm(u,(int)u[1][0],(int)u[2][0],0,f);

for(int i=2;i<=hid;i++)
{
u=dotppp(Hidd[i].widt,u,Hidd[i].nr_l,Hidd[i].nr_c,u[1][0],u[2][0]);


add2(u,convert2(Hidd[i].bias,Hidd[i].nr_l,p),Hidd[i].nr_l,p);
mapm(u,(int)u[1][0],(int)u[2][0],0,f);

}



//cout<<"uses"<<endl;
//sca2d(u,u[1][0],u[2][0]);


T** ou=dotppp(Out_nodes.widt,u,Out_nodes.nr_l,Out_nodes.nr_c,u[1][0],u[2][0]);

add2(ou,convert2(Out_nodes.bias,Out_nodes.nr_l,p),Out_nodes.nr_l,p);

mapm(ou,(int)ou[1][0],(int)ou[2][0],0,f);

return ou;
}





template<typename T,typename R>
T** backprop(T* a,T* b,int n,int m,int n2,int m2,R o=0,T(*f)(T,R)=dsigmoid)
{

T** errr=new T*[hid+3];


T** er=convert2(a,n,m);
T** d=convert2(b,n2,m2);
er[1][0]=n;er[2][0]=m;d[1][0]=n2;d[2][0]=m2;

//sca2d(er,n,m);
//sca2d(d,n2,m2);


er=diffm(er,d);

errr[0][0]=hid+2;

errr[1]=convert(er,er[1][0],er[2][0]);

//sca2d(er,er[1][0],er[2][0]);
cout<<"pizza"<<endl;


//transp(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c),Out_nodes.nr_l,Out_nodes.nr_c)



d=dotppp(transp(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c),er,Out_nodes.nr_c,Out_nodes.nr_l,er[1][0],er[2][0]);

errr[2]=convert(d,d[1][0],d[2][0]);

sca2d(d,d[1][0],d[2][0]);

er=d;


for(int i=hid;i>=1;i--)
{
cout<<"trans"<<endl;

sca2d(er,er[1][0],er[2][0]);


sca2d(transp(Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c),Hidd[i].nr_c,Hidd[i].nr_l);


d=dotppp(transp(Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c),er,Hidd[i].nr_c,Hidd[i].nr_l,er[1][0],er[2][0]);
errr[2+hid-i+1]=convert(d,d[1][0],d[2][0]);


cout<<"d"<<endl;

//sca2d(d,d[1][0],d[2][0]);
cout<<"er"<<endl;
//sca2d(er,er[1][0],er[2][0]);
er=d;
}

return errr;
}


void print_network2(int se=1)
{
   int n=0;
   if(se==2 && Inp_nodes.widt!=NULL)

   {
  cout<<"input["<<Inp_nodes.nr_l*Inp_nodes.nr_c<<"]"<<endl;

n+=Inp_nodes.nr_l*Inp_nodes.nr_c;

sca2d(Inp_nodes.widt,Inp_nodes.nr_l,Inp_nodes.nr_c);
   }

cout<<"hidden layers"<<endl;
   for(int i=1;i<=hid;i++)
   {
      cout<<"hiddlayer["<<i<<"]["<<Hidd[i].nr_l*Hidd[i].nr_c<<"]"<<endl;
      n+=Hidd[i].nr_l*Hidd[i].nr_c;
      n+=Hidd[i].nr_l;
   //sca2d(Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c);
    cout<<"byas hidden"<<endl;
   sca(Hidd[i].bias,Hidd[i].nr_l);
   }


     //cout<<"output layer"<<endl;
   //sca2d(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c);
    cout<<"output layer["<<Out_nodes.nr_l*Out_nodes.nr_c<<"]"<<endl;
    n+=Out_nodes.nr_l*Out_nodes.nr_c;
    cout<<"byas hidden"<<endl;
   sca(Out_nodes.bias,Out_nodes.nr_l);
n+=Out_nodes.nr_l;

   cout<<"memory used"<<n<<endl;

;

}

void print_network(int se=1)
{
   if(se==2 && Inp_nodes.widt!=NULL)

   {
  cout<<"input";
sca2d(Inp_nodes.widt,Inp_nodes.nr_l,Inp_nodes.nr_c);
   }

cout<<"hidden layers"<<endl;
   for(int i=1;i<=hid;i++)
   {
      cout<<"layer"<<i<<endl;
   sca2d(Hidd[i].widt,Hidd[i].nr_l,Hidd[i].nr_c);
    cout<<"byas hidden"<<endl;
   sca(Hidd[i].bias,Hidd[i].nr_l);
   }

     cout<<"output layer"<<endl;
   sca2d(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c);
    cout<<"byas hidden"<<endl;
   sca(Out_nodes.bias,Out_nodes.nr_l);

;

}










void randomizen()
{
   make_hidtr2(hid,Hidd[1].nr_l,Inp_nodes.nr_l,-10,10);

   Out_nodes.widt=Out_nodes.rand_widt(Out_nodes.nr_l,Hidd[1].nr_l,-10,10);

   Out_nodes.bias=Out_nodes.rand_bias(Out_nodes.nr_l);

}


void Set_dropout(double p=0,int exists=1)
{
   drop=exists;
   if(drop)drop_p=p;
}


void retiered(double p=1.1,double a[]=NULL)
{
 if(a==NULL)
 {
if(randf(0,1)<=p)
{
   int rl=1+rand()%(hid+1);
   int rn;

   if(rl==hid+1)rn=1+rand()%Out_nodes.nr_l;
   else
    rn=1+rand()%Hidd[rl].nr_l;
    int n;
    if(rl==hid+1)
    n=Out_nodes.nr_c;
    else
    n=Hidd[rl].nr_c;
for(int i=1;i<=n;i++)
{
if(rl==hid+1)Out_nodes.widt[rn][i]=0.1;
else
Hidd[rl].widt[rn][i]=0.1;
}
if(rl==hid+1)Out_nodes.bias[rn]=0;
else
   Hidd[rl].bias[rn]=0;
}
 }
 else
 {
int j=1;
int ur;
int uc;
double u=randf(0,1);
  while(  j<=hid+1 && u<a[j])j++;
 if(j<=hid)
 {
   ur=1+rand()%Hidd[j].nr_l;
   uc=Hidd[j].nr_c;
 }
 else
 {
    ur=1+rand()%Out_nodes.nr_l;
    uc=Out_nodes.nr_c;
 }

  for(int i=1;i<=uc;i++)
  {
     if(j<=hid){Hidd[j].widt[ur][i]=0.1; Hidd[j].bias[ur]=0;}
       else
      {Out_nodes.widt[ur][i]=0.1; Out_nodes.bias[ur]=0;}
  }

 }


}

void repare_nan()
{


   for(int i=1;i<=hid;i++)
    for(int j=1;j<=Hidd[i].nr_l;j++)
      for(int k=1;k<=Hidd[i].nr_c;k++)
    if(isnan(Hidd[i].widt[j][k]))
      Hidd[i].widt[j][k]=0.1;

   for(int j=1;j<=Out_nodes.nr_l;j++)
      for(int k=1;k<=Out_nodes.nr_c;k++)
    if(isnan(Out_nodes.widt[j][k]))Out_nodes.widt[j][k]=0.1;


   for(int i=1;i<=hid;i++)
    for(int j=1;j<=Hidd[i].nr_l;j++)
    if(isnan(Hidd[i].bias[j]))Hidd[i].bias[j]=0;


   for(int j=1;j<=Out_nodes.nr_l;j++)
    if(isnan(Out_nodes.bias[j]))Out_nodes.bias[j]=0;


}


void mutate(double r)
{
   for(int i=1;i<=Out_nodes.nr_l;i++)
   for(int j=1;j<=Out_nodes.nr_c;j++)
    if(randf(0,1)<=r)Out_nodes.widt[i][j]=randf(-10,10);

   for(int k=1;k<=hid;k++)
   {
   for(int i=1;i<=Hidd[k].nr_l;i++)
   for(int j=1;j<=Hidd[k].nr_c;j++)
    if(randf(0,1)<=r)Hidd[k].widt[i][j]=randf(-10,10);
   }
}



void mutate2(double r)
{
   for(int i=1;i<=Out_nodes.nr_l;i++)

   {
   if(randf(0,1)<=r)Out_nodes.bias[i]+=randf(-1,1);

   for(int j=1;j<=Out_nodes.nr_c;j++)
    if(randf(0,1)<=r)Out_nodes.widt[i][j]+=randf(-1,1);

   }



   for(int k=1;k<=hid;k++)
   {
   for(int i=1;i<=Hidd[k].nr_l;i++)
   {
      if(randf(0,1)<=r)Hidd[k].bias[i]+=randf(-1,1);
   for(int j=1;j<=Hidd[k].nr_c;j++)

    if(randf(0,1)<=r)Hidd[k].widt[i][j]+=randf(-1,1);
   }
   }

}



double random_gausian(double m,double d)
{
   double x=randf(-5,5);

   double first=1.0/(sqrm(2*pi*d*d));
   double sec=Math.expo(-(x-m)*(x-m)/(2*(d*d)));

   return first*sec;

}


void mutate3(double r)
{

   for(int i=1;i<=Out_nodes.nr_l;i++)

   {
   if(randf(0,1)<=r)Out_nodes.bias[i]+=randf(-1,1);

   for(int j=1;j<=Out_nodes.nr_c;j++)
    if(randf(0,1)<=r)Out_nodes.widt[i][j]+=randf(-1,1);

   }

   for(int k=1;k<=hid;k++)
   {
   for(int i=1;i<=Hidd[k].nr_l;i++)
   {
      if(randf(0,1)<=r)Hidd[k].bias[i]+=random_gausian(0,0.5);
   for(int j=1;j<=Hidd[k].nr_c;j++)

    if(randf(0,1)<=r)Hidd[k].widt[i][j]+random_gausian(0,0.5);
   }
   }

}













double POS=0;



template<typename T,typename R>
T** train(T* a,T* b,int n,int m,int n2,int m2,R o=0,T(*f)(T,R)=sigmoid,T(*f2)(T,R)=arsigmoid)
{
//feedforward part


//print_network();

if(drop)retiered(drop_p,NULL);

Chiler_network();


give_data(convert2(a,n,m),n,m);

repare_nan();



//cout<<"trecut peste"<<endl;






//cout<<"inputs"<<endl;
//sca2d(Inp_nodes.widt,n,m);



T** u=dotppp(Hidd[1].widt,Inp_nodes.widt,Hidd[1].nr_l,Hidd[1].nr_c,Inp_nodes.nr_l,Inp_nodes.nr_c);

int p=1;




if(Hidd[1].bias!=NULL)
add2(u,convert2(Hidd[1].bias,Hidd[1].nr_l,p),Hidd[1].nr_l,p);



//sca2d(u,u[1][0],u[2][0]);

mapm(u,(int)u[1][0],(int)u[2][0],0,f);




for(int i=2;i<=hid;i++)
{
u=dotppp(Hidd[i].widt,u,Hidd[i].nr_l,Hidd[i].nr_c,u[1][0],u[2][0]);

add2(u,convert2(Hidd[i].bias,Hidd[i].nr_l,p),Hidd[i].nr_l,p);

mapm(u,(int)u[1][0],(int)u[2][0],0,f);


//cout<<"hid"<<i<<endl;

//sca2d(u,u[1][0],u[2][0]);
}
;
//sca2d(u,u[1][0],u[2][0]);
//cout<<"OUTPUT-LAYER"<<endl;
//sca2d(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c);


T** ou;




ou=dotppp(Out_nodes.widt,u,Out_nodes.nr_l,Out_nodes.nr_c,u[1][0],u[2][0]);



if(Out_nodes.bias)
add2(ou,convert2(Out_nodes.bias,max(3,Out_nodes.nr_l),max(3,p),Out_nodes.nr_l,p),Out_nodes.nr_l,p);



mapm(ou,(int)ou[1][0],(int)ou[2][0],0,f);







T** er=copym(ou,ou[1][0],ou[2][0]);






int op1=0,op2=0;

if(n2==1)op1=2;
if(m2==1)op2=2;




T** d=convert2(b,max(3,n2),max(3,m2),n2,m2);










er=diffm(d,ou);




cout<<"int-put";

sca2d(convert2(a,n,m),n,m);





cout<<"out-put";

sca2d(d,d[1][0],d[2][0]);


cout<<"real out-put";

sca2d(ou,ou[1][0],ou[2][0]);


cout<<"erori"<<endl;

sca2d(er,er[1][0],er[2][0]);

POS+=er[1][1];

cout<<"gata erori"<<endl;

//cout<<"outer"<<Out_nodes.nr_c<<" "<<Out_nodes.nr_l<<endl;

//sca2d(transp(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c),Out_nodes.nr_c,Out_nodes.nr_l);

//cout<<Out_nodes.nr_c<<Out_nodes.nr_l<<er[1][0]<<er[2][0]<<endl;


d=dotppp(transp(Out_nodes.widt,Out_nodes.nr_l,Out_nodes.nr_c),er,Out_nodes.nr_c,Out_nodes.nr_l,er[1][0],er[2][0]);






//sca2d(d,d[1][0],d[2][0]);




int us1,us2;


T** r=mapmp(ou,(int)ou[1][0],(int)ou[2][0],0,f2);


mult2(r,er,r[1][0],r[2][0]);


opm(r,r[1][0],r[2][0],lr,2);




T** ht;
T** dw;


ht=transp(u,u[1][0],u[2][0]);






dw=dotppp(r,ht,r[1][0],r[2][0],ht[1][0],ht[2][0]);




add2(Out_nodes.widt,dw,Out_nodes.nr_l,Out_nodes.nr_c);

er=d;




T** ua=convert2(Out_nodes.bias,r[1][0],r[2][0]);




add2(ua,r,ua[1][0],ua[2][0]);


us1=ua[1][0];
us2=ua[2][0];




Out_nodes.bias=convert(ua,us1,us2);



//cout<<"gata aici";


Chiler_network();
repare_nan();



for(int j=hid;j>=2;j--)
{

d=dotppp(transp(Hidd[j].widt,Hidd[j].nr_l,Hidd[j].nr_c),er,Hidd[j].nr_c,Hidd[j].nr_l,er[1][0],er[2][0]);




us1=er[1][0];

us2=er[2][0];


u=dotppp(Hidd[1].widt,Inp_nodes.widt,Hidd[1].nr_l,Hidd[1].nr_c,Inp_nodes.nr_l,Inp_nodes.nr_c);



add2(u,convert2(Hidd[1].bias,Hidd[1].nr_l,p),Hidd[1].nr_l,p);
mapm(u,(int)u[1][0],(int)u[2][0],(int)0,f);






for(int i=2;i<=j;i++)
{
u=dotppp(Hidd[i].widt,u,Hidd[i].nr_l,Hidd[i].nr_c,u[1][0],u[2][0]);

add2(u,convert2(Hidd[i].bias,Hidd[i].nr_l,p),Hidd[i].nr_l,p);
mapm(u,(int)u[1][0],(int)u[2][0],(int)0,f);
}


//cout<<"gata aici 2"<<endl;



//compute the gradient
T** hg1=mapmp(u,(int)u[1][0],(int) u[2][0],0,f2);

mult2(hg1,er,er[1][0],er[2][0]);

opm(hg1,hg1[1][0],hg1[2][0],lr,2);

ua=convert2(Hidd[j].bias,hg1[1][0],hg1[2][0]);
add2(ua,hg1,hg1[1][0],hg1[2][0]);
us1=hg1[1][0];
us2=hg1[2][0];
Hidd[j].bias=convert(ua,us1,us2);

//delete[]ua;

//feed forward compute input for the hidden


//delete[] u;
u=dotppp(Hidd[1].widt,Inp_nodes.widt,Hidd[1].nr_l,Hidd[1].nr_c,Inp_nodes.nr_l,Inp_nodes.nr_c);

if(Hidd[1].bias!=NULL)
add2(u,convert2(Hidd[1].bias,Hidd[1].nr_l,p),Hidd[1].nr_l,p);
mapm(u,(int)u[1][0],(int)u[2][0],(int)0,f);

for(int i=2;i<j;i++)
{
u=dotppp(Hidd[i].widt,u,Hidd[i].nr_l,Hidd[i].nr_c,u[1][0],u[2][0]);

add2(u,convert2(Hidd[i].bias,Hidd[i].nr_l,p),Hidd[i].nr_l,p);
mapm(u,(int)u[1][0],(int)u[2][0],(int)0,f);

}


ht=transp(u,u[1][0],u[2][0]);

dw=dotppp(hg1,ht,hg1[1][0],hg1[2][0],ht[1][0],ht[2][0]);

add2(Hidd[j].widt,dw,Hidd[j].nr_l,Hidd[j].nr_c);

//delete [] dw;delete[] ht;delete[] hg1;

//delete[] er;
er=d;

Chiler_network();
repare_nan();


}
//cout<<"gata aici 3"<<endl;


//cout<<"gata hidden except for 1"<<endl;



//delete[] u;
u=dotppp(Hidd[1].widt,Inp_nodes.widt,Hidd[1].nr_l,Hidd[1].nr_c,Inp_nodes.nr_l,Inp_nodes.nr_c);
add2(u,convert2(Hidd[1].bias,Hidd[1].nr_l,p),Hidd[1].nr_l,p);
mapm(u,(int)u[1][0],(int)u[2][0],(int)0,f);



T** it=transp(Inp_nodes.widt,Inp_nodes.nr_l,Inp_nodes.nr_c);


T** hg1=mapmp(u,(int)u[1][0],(int) u[2][0],0,f2);


//d=dotppp(transp(Hidd[1].widt,Hidd[1].nr_l,Hidd[1].nr_c),er,Hidd[1].nr_c,Hidd[1].nr_l,er[1][0],er[2][0]);

mult2(hg1,er,er[1][0],er[2][0]);

opm(hg1,hg1[1][0],hg1[2][0],lr,2);

//cout<<"error now";
//sca2d(d,d[1][0],d[2][0]);


ua=convert2(Hidd[1].bias,hg1[1][0],hg1[2][0]);

add2(ua,hg1,hg1[1][0],hg1[2][0]);

us1=hg1[1][0];
us2=hg1[2][0];
Hidd[1].bias=convert(ua,us1,us2);


dw=dotppp(hg1,it,hg1[1][0],hg1[2][0],it[1][0],it[2][0]);

add2(Hidd[1].widt,dw,Hidd[1].nr_l,Hidd[1].nr_c);
//cout<<"hiddent"<<1<<endl;
//sca2d(Hidd[1].widt,Hidd[1].nr_l,Hidd[1].nr_c);




return NULL;
}



void setLearningRate(double lrr=0.1)
{
   lr=lrr;
}


void sendN(char* s)
{


   ofstream f(s);



   f<<lr<<endl;
   f<<drop<<" "<<drop_p<<endl<<endl;

   f<<hid<<endl;

   for(int i=1;i<=hid;i++)
   {
      f<<Hidd[i].nr_l<<" ";
      f<<Hidd[i].nr_c;
      f<<endl;

      for(int k=1;k<=Hidd[i].nr_l;k++)
      {

        for(int j=1;j<=Hidd[i].nr_c;j++)
           f<<Hidd[i].widt[k][j]<<" ";
      f<<endl;
      }

      f<<endl<<endl;


      f<<Hidd[i].nr_l<<endl;
       for(int k=1;k<=Hidd[i].nr_l;k++)
      f<<Hidd[i].bias[k]<<" ";
       f<<endl;
   }





   f<<Out_nodes.nr_l<<' ';
   f<<Out_nodes.nr_c<<endl;


      for(int k=1;k<=Out_nodes.nr_l;k++)
      {

        for(int j=1;j<=Out_nodes.nr_c;j++)
           f<<Out_nodes.widt[k][j]<<" ";
      f<<endl;
      }
      f<<endl<<endl;



      f<<Out_nodes.nr_l<<endl;
       for(int k=1;k<=Out_nodes.nr_l;k++)
      f<<Out_nodes.bias[k]<<" ";
      f<<endl;

   }



void read(char* s)
{
    ifstream f(s);

   f>>lr;
   f>>drop>>drop_p;
   f>>hid;
Hidd=new Layer[hid+2];
   for(int i=1;i<=hid;i++)
   {
      f>>Hidd[i].nr_l;
      f>>Hidd[i].nr_c;


      Hidd[i].widt=new double*[Hidd[i].nr_l+2];
      for(int k=0;k<=Hidd[i].nr_l+2;k++)
  Hidd[i].widt[k]=new double[Hidd[i].nr_c+2+1];



      for(int k=1;k<=Hidd[i].nr_l;k++)
      {


        for(int j=1;j<=Hidd[i].nr_c;j++)
           f>>Hidd[i].widt[k][j];
      }

      f>>Hidd[i].nr_l;
      Hidd[i].bias=new double[Hidd[i].nr_l+2];

       for(int k=1;k<=Hidd[i].nr_l;k++)
      f>>Hidd[i].bias[k];

   }





   f>>Out_nodes.nr_l;
   f>>Out_nodes.nr_c;


  Out_nodes.widt=new double*[Out_nodes.nr_l+2];



      for(int i=0;i<=Out_nodes.nr_l+2;i++)
  Out_nodes.widt[i]=new double[Out_nodes.nr_c+2];



      for(int k=1;k<=Out_nodes.nr_l;k++)
      {


        for(int j=1;j<=Out_nodes.nr_c;j++)
           f>>Out_nodes.widt[k][j];
      }

      f>>Out_nodes.nr_l;
      Out_nodes.bias=new double[Out_nodes.nr_l+2];

       for(int k=1;k<=Out_nodes.nr_l;k++)
      f>>Out_nodes.bias[k];


   f.close();
}














};
































struct Conv_Neuron
{
   int n, m;
   int stride=1;
  double** filter;

   void pre_make(int n,int m)
   {
      filter=new double*[n+1];

      for(int i=0;i<=n;i++)
      filter[i]=new double[m+1];

   }






 double** conv(double** a,int n2,int m2,int uf=1,double(*f)(double,int)=Relu)
{

double** result=new double*[n+2];
for(int i=0;i<=n+1;i++)
result[i]=new double[m+2];

int wi=0, hi=0;

for(int i=1;i<=n2;i+=stride)
{

   if(i+n<=n2+1)hi++;
   wi=0;

   for(int j=1;j<=m2;j+=stride)
   {
      if(j+m<=m2+1)wi++;

      result[hi][wi]=0;

   //receptive field
      for(int h=0;h<n;h++)
      {
      for(int w=0;w<m;w++)

      if(i+h<=n2 && j+w<=m2)
         result[hi][wi]+=filter[h+1][w+1]*a[i+h][j+w];
      }
   }
   }

result[1][0]=hi;
result[2][0]=wi;

if(uf==1)
 mapm(result,(int)result[1][0],(int)result[2][0],(int)0,f);


return result;

}




};

struct Pooling
{

int n, m;
int strides=1;
int avm=0;
  double** max_pool(double** mat,int n1,int m1,int& rn,int& rm)
   {
      int h=1,w=1;
      double** res=new double*[n1/n+2];
      for(int i=1;i<=n1/n+1;i++)
      res[i]=new double[m1/m+2];



     int i=1,j=1;
     while(i<=n1 && j<=m1)
   {
         int maxi=-INFINITE;


          for(int k=1;k<=n;k++)
         for(int l=1;l<=m;l++)
      if(mat[i+k-1][j+l-1]>maxi)maxi=mat[i+k-1][j+l-1];

      res[h][w]=maxi;


      if(j<m1){j=j+strides;w++;}

      else

      {
         i=i+strides;h++;
         rm=w;
         j=1;w=1;
      }
   }
   rn=h;
   return res;

   }


   double** Average_pool(double** mat,int n1,int m1,int& rn,int& rm)
   {
      int h=1,w=1;
      double** res=new double*[n1/n+2];
      for(int i=1;i<=n1/n+1;i++)
      res[i]=new double[m1/m+2];



     int i=1,j=1;
     while(i<=n1 && j<=m1)
   {
         int suma=0;


          for(int k=1;k<=n;k++)
         for(int l=1;l<=m;l++)
         suma+=mat[i+k-1][j+l-1];

      res[h][w]=suma/(n*m);


      if(j<m1){j=j+strides;w++;}
      else
      {
         i=i+strides;h++;
         rm=w;
         j=1;w=1;
      }
   }
   rn=h;
   return res;

   }







};



struct Convlayer
{


Conv_Neuron* neurons;
   int n;

   void make(int n2)
   {
      neurons=new Conv_Neuron[n2+2];
      n=n2;
   }

   struct Output
{
  int depth;
   Conv_Neuron* results;


   }out_volume;









};


struct Convolutive
{

   int* strc;
   int n,k,p;
   Convlayer* conv_layer;
   Pooling* pool;



};


















struct Neural_Network
{

double pool_size;
double learn_rate;
int nr_layers;

Layer* lay;

void C_N(int n,int l_r=0.5,int ps=2)
{

nr_layers=n;
lay=new Layer[n+2];
learn_rate=l_r;
pool_size=ps;

}
void n_l(int i,int n)
{

}



template<typename T>
T** cnn_layer(T** image,int n,int m,int layer_i=1)
{

T** acasa;


acasa=convolution(image,lay[layer_i].widt,n,m,lay[layer_i].nr_c,lay[layer_i].nr_l);

acasa=Multm(acasa,acasa[1][0],acasa[2][0],lay[layer_i].bias[1]);


return acasa;

};




};

Layer& layer(Neural_Network& nc,int layer_i=1)
{

return nc.lay[layer_i];

}






struct Weights{

double** a;
double* b;
int linii,coloane;

Weights* load_weigths(Weights* w,char a[])
{

   ifstream rd(a);


int n;
   rd>>n;

   w=new Weights[n+1];


   w[0].linii=n;

for(int i=1;i<=n;i++)
   {
      rd>>w[i].linii;
      rd>>w[i].coloane;

      w[i].a=new double*[w[i].linii+1];

      for(int k=0;k<=w[i].linii;k++)
         w[i].a[k]=new double[w[i].coloane+1];


      for(int x=1;x<=w[i].linii;x++)
       for(int y=1;y<=w[i].coloane;y++)
      rd>>w[i].a[x][y];

      w[i].a[1][0]=w[i].linii;
      w[i].a[2][0]=w[i].coloane;

      rd>>n;
      w[i].b=new double[n+2];
   for(int j=1;j<=n;j++)
      rd>>w[i].b[j];


   }

   return w;
}

void transfer(Weights*w,Neural_Network& d)
{

   d.lay=new Layer[w[0].linii+1];




for(int i=1;i<=w[0].linii;i++)
{
   d.lay[i].widt=new double*[w[i].linii+1];


   d.lay[i].nr_c= w[i].coloane;

   d.lay[i].nr_l= w[i].linii;

   for(int j=1;j<=w[i].linii;j++)
   d.lay[i].widt[i]=new double[ w[i].coloane ];

   move_pp(d.lay[i].widt, w[i].a,w[i].linii,w[i].coloane);

}


}

};




struct LSTM_Cell
{

  double sigmoid(double x)
   {
      return exp(x)/(1+exp(x));

   }

     double tanh(double x)
   {
      return (exp(x)-1.0/exp(x))/(exp(x)+1.0/exp(x));

   }







};





























#endif // NEURAL NETWORK_H
