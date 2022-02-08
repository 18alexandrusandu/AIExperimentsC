#ifndef NEURO-GENETIC1_H
#define NEURO-GENETIC1_H

#include"math-motions/ss_graff.h"
#include"neural network2.h"


template<typename T>
void calc_fitt(T** b,int n)
{
   double c=0,f=0;

   for(int i=1;i<=n;i++)
   { c+=b[i]->score;
   }

    for(int i=1;i<=n;i++)
   { b[i]->fitness=c/b[i]->score;
   }


}

 int sv;


 template<typename T>
 T* pickOne(T* b[],int n)
 {
 int index=1;
 float t=randf(0,1);
 while(t>0)
 {
    t=t-b[index]->fitness;
    index++;
 }

 index--;
 T* bu=b[index];

T* f=new T(bu->brain);

f->brain.mutate(0.1);

return f;

}


///  b must respect the following rules: being a structure or class with elements double fitness,score and a Neural_NetworkSD called brain ,as well as a constructor for the class given that takes like parameter a Neural_NetworkSD
template<typename T>
 void next_generation(T**  b,int n)
 {
    calc_fitt(b,n);

    for(int i=1;i<=n;i++)
    {
    b[i]= pickOne(b,n);
     }
     sv=0;

}



#endif // NEURO



