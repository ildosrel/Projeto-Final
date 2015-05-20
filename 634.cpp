//Anderson Zudio de Moraes
//Julio Cesar
//Victor Cracel Messner
//AC 31/05/2014
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
typedef struct {int x, y;}Ponto;
typedef struct {Ponto p, q;}Segmento;
Ponto pol[100000], pols[100000]; //vetores globais

int SentidoPercurso(Ponto p1, Ponto p2, Ponto p3)
{  long long a, b, c, d;
   a= p2.x - p1.x;  b= p3.y - p1.y;  c=p3.x - p1.x;  d=p2.y - p1.y;
   a = a*b-c*d;
   if (a > 0) return 1;
   else if (a < 0) return -1;
   else return 0;
}
int Intercepta(Segmento s1, Segmento s2)
{  if ((max(s1.p.x,s1.q.x)>=min(s2.p.x,s2.q.x))&&
       (max(s2.p.x,s2.q.x)>=min(s1.p.x,s1.q.x))&&
       (max(s1.p.y,s1.q.y)>=min(s2.p.y,s2.q.y))&&
       (max(s2.p.y,s2.q.y)>=min(s1.p.y,s1.q.y))&&
       (SentidoPercurso(s1.p,s1.q,s2.p)*SentidoPercurso(s1.p,s1.q,s2.q)<=0)&&
       (SentidoPercurso(s2.p,s2.q,s1.p)*SentidoPercurso(s2.p,s2.q,s1.q)<=0))
       return 1;
    else return 0;
}
double AreaPoligono(int n)
{  long long c;  int i;
   c = 0;  for (i=0; i<n; i++) c= c + pol[i].x*pol[i+1].y-pol[i+1].x*pol[i].y;
   return c/2.0;
}
void Quicksort(int e, int d)
// O ponto 0 fica fixo na ordena��o, pois tem o menor x
{  int i,j,k;  Ponto t,r;  long long d0, d1, d2;
   if (d > e)
   {  i=e;  j=d;  t=pol[(e+d)/2];
      d1= pol[0].x-t.x;  d2= pol[0].y-t.y;  d0=d1*d1+d2*d2;
      while(i<=j)
      {  while(1)
         {  k=SentidoPercurso(pol[0],pol[i],t);
            if (k==1) i++;
            else if (k==0)
            {  d1= pol[0].x-pol[i].x;  d2= pol[0].y-pol[i].y;  d1= d1*d1+d2*d2;
               if (d1 < d0) i++;
               else break;
            }
            else break;
         }
         while(1)
         {  k=SentidoPercurso(pol[0],t,pol[j]);
            if (k==1) j--;
            else if (k==0)
            {  d1= pol[0].x-pol[j].x;  d2= pol[0].y-pol[j].y;  d1= d1*d1+d2*d2;
               if (d0 < d1) j--;
               else break;
            }
            else break;
         }
         if (i<=j) {r=pol[i];  pol[i]=pol[j];  pol[j]=r;  i++; j--;}
      }
      Quicksort(e,j);  Quicksort(i,d);
   }
}
void OrdenaPontosy(int tp)
/*   Ordena pontos por �ngulo, escolhendo como refer�ncia o ponto mais embaixo e mais
   � esquerda. */
{  int i,m;  Ponto p;
   m=0;
   for (i=1;i<tp;i++)
      if ((pol[i].y < pol[m].y)||(pol[i].y==pol[m].y)&&(pol[i].x<pol[m].x)) m=i;
   p=pol[0];  pol[0]=pol[m];  pol[m]=p;
   Quicksort(1,tp-1);
}
void OrdenaPontosx(int tp)
/* Ordena pontos por �ngulo, escolhendo como refer�ncia o ponto mais � esquerda e mais
   embaixo. */
{  int i,m;  Ponto p;
   m=0;
   for (i=1;i<tp;i++)
      if ((pol[i].x < pol[m].x)||(pol[i].x==pol[m].x)&&(pol[i].y<pol[m].y)) m=i;
   p=pol[0];  pol[0]=pol[m];  pol[m]=p;
   Quicksort(1,tp-1);
}
void CaminhoFechado(int tp)
/* Ordena pontos e, ao final da ordena��o, se houver pontos colineares com
   o ponto inicial, no final do vetor, a ordem dos pontos colineares � invertida. */
{  int i,m;  Ponto p;
   OrdenaPontosx(tp);
   i = tp-1;  while ((i>0)&&(SentidoPercurso(pol[0],pol[i-1],pol[i])==0)) i--;
   for (m=i; m<(i+tp)/2;m++) {p=pol[m]; pol[m]=pol[tp-1-m+i]; pol[tp-1-m+i]=p;}
}

int ConvexHull(int t)
{   int i,j,topo;
    OrdenaPontosy(t);
    /*Repete o ponto inicial no final*/
    pols[0]= pol[0]; pol[t]= pol[0];
    j= 1;
    /* Elimina pontos iniciais colineares */
    while (SentidoPercurso(pols[0],pol[j],pol[j+1])==0) j++;
    pols[1]= pol[j];  pols[2]= pol[j+1];
    topo= 2;
    for (i= j+2; i<= t;i++)
    {   while (SentidoPercurso(pols[topo-1], pols[topo], pol[i]) <= 0) topo--;
        topo++;  pols[topo]= pol[i];
    }
    return (topo);
}
void ExemploSentidoPercurso(){
    Ponto p1,p2,p3;  int j;
    cout<<"Exemplo de uso de SentidoPercurso"<<endl;
    cout<< "Entre com as coordenadas (x,y) de p1, p2 e p3: ";
    cin>>p1.x >>p1.y >>p2.x >>p2.y >>p3.x >>p3.y;
    j= SentidoPercurso(p1,p2,p3);
    if (j==1)       cout<<"Antihorario"<<endl;
    else if (j==-1) cout<<"Horario" <<endl;
    else            cout<<"Pontos colineares"<<endl;
    cout<<endl;
}

void ExemploIntersecaoSegmentos(){
    Segmento s1,s2;
    cout<<"Exemplo de uso de Intercepta" <<endl;
    cout<<"Entre com o segmento 1 (p1 e p2): ";
    cin>> s1.p.x >> s1.p.y >> s1.q.x >> s1.q.y;
    cout<< "Entre com o segmento 2 (p3 e p4): ";
    cin>> s2.p.x >> s2.p.y >> s2.q.x >> s2.q.y;
    if (Intercepta(s1,s2)==1) cout<< "Interceptam" <<endl;
    else cout<< "Nao interceptam" <<endl;
    cout<<endl;
}

void ExemploAreaPoligono(){
    int i, np;
    cout<< "Exemplo de uso de AreaPoligono" <<endl;
    cout<< "Entre com o n�mero de vertices: ";  cin>> np;
    for (i=0; i<np; i++) {
        cout<< "Entre com o ponto " <<i+1 <<" : ";
        cin>> pol[i].x >>pol[i].y;
    }
    pol[np] = pol[0];
    cout<<"Area do poligono = " <<AreaPoligono(np) <<endl;
    cout<<endl;
}

void ExemploCaminhoFechado(){
    int i, np;
    cout<< "Exemplo de uso de CaminhoFechado" <<endl;
    cout<< "Entre com o n�mero de pontos: ";  cin>> np;
    for (i=0; i<np; i++) {
        cout<< "Entre com o ponto " <<i+1 <<" : ";
        cin>> pol[i].x >>pol[i].y;
    }
    CaminhoFechado(np);
    cout<<"Caminho fechado:";
    for (i=0; i<np; i++) cout<< pol[i].x <<" " <<pol[i].y <<" ";
    cout<<endl<<endl;
}

void ExemploContornoConvexo(){
    int i, np, nv;
    cout<< "Exemplo de uso de ConvexHull" <<endl;
    cout<< "Entre com o n�mero de pontos: ";  cin>> np;
    for (i=0; i<np; i++) {
        cout<< "Entre com o ponto " <<i+1 << " : ";
        cin>> pol[i].x >>pol[i].y;
    }
    nv = ConvexHull(np);
    cout<<"Contorno Convexo com " <<nv-1 <<" pontos:";
    for (i=0; i<=nv; i++) cout<< pols[i].x <<" " <<pols[i].y <<" ";
    cout<<endl<<endl;
}

bool PontoInterior(Ponto q, int n){
    Segmento s, s1;
    Ponto qf;
    int cont;
    pol[0] = pol[n];
    for(int i = 1; i <= n; i++){
        s.p = pol[i-1]; s.q = pol[i]; s1.p = q; s1.q = q;
        if(((pol[i].x == q.x) && (pol[i].y == q.y)) || Intercepta(s,s1)) return true;
    }
    qf.x = 99999; qf.y = q.y; cont = 0;

    for(int i = 1; i <= n; i++){
        s.p = q; s.q = qf; s1.p = pol[i-1]; s1.q = pol[i];
        if((((pol[i].y > q.y) && (pol[i-1].y <= q.y)) || ((pol[i-1].y > q.y) && (pol[i].y <= q.y))) && (Intercepta(s,s1)))
            cont++;
    }
    return((cont % 2) != 0);


}


void Solucao(int n){
    Ponto q;
    for(int i = 1; i <= n; i++)
        cin >> pol[i].x >> pol[i].y;
    cin >> q.x >> q.y;
    if(PontoInterior(q, n)) cout << "T" << endl;
    else cout << "F" << endl;

}

int main()
{
    int n;
    while(cin >> n, n){
        Solucao(n);
    }
    return 0;
}
