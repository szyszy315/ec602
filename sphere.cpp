// Copyright 2019 zeyu song zeyusong@bu.edu
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std; 


class spheres
{
public:
  double mass;
  double radius;
  std::vector<double> velocity;
  std::vector<double> position;
  string name;
  int count;
  double container;
};

vector<double> addv(vector<double> a,vector<double> b){
  std::vector<double> v;
  v.push_back(a.at(0)+b.at(0));
  v.push_back(a.at(1)+b.at(1));
  v.push_back(a.at(2)+b.at(2));
  return v;
}

vector<double> mulv(vector<double> a,vector<double> b){
  std::vector<double> v;
  v.push_back(a.at(0)*b.at(0));
  v.push_back(a.at(1)*b.at(1));
  v.push_back(a.at(2)*b.at(2));
  return v;
}


vector<double> subv(vector<double> a,vector<double> b){
  std::vector<double> v;
  v.push_back(a.at(0)-b.at(0));
  v.push_back(a.at(1)-b.at(1));
  v.push_back(a.at(2)-b.at(2));
  return v;
}

double dotproduct(vector<double> a,vector<double> b){
  return a.at(0)*b.at(0)+a.at(1)*b.at(1)+a.at(2)*b.at(2);
}


vector<double> mult2vector(vector<double> a,vector<double> b){
  std::vector<double> v;
  v.push_back(a.at(1)*b.at(2)-a.at(2)*b.at(1));
  v.push_back(a.at(0)*b.at(2)-b.at(0)*a.at(2));
  v.push_back(a.at(0)*b.at(1)-a.at(1)*b.at(0));
  return v;
}


double predict(spheres s1,spheres s2){
  double a = pow(s1.velocity.at(0)-s2.velocity.at(0),2)+ pow(s1.velocity.at(1)-s2.velocity.at(1),2)+ pow(s1.velocity.at(2)-s2.velocity.at(2),2);
  double b = 2*(s1.position.at(0)-s2.position.at(0))*(s1.velocity.at(0) - s2.velocity.at(0))+ 2*(s1.position.at(1)-s2.position.at(1))*(s1.velocity.at(1) - s2.velocity.at(1))+ 2*(s1.position.at(2)-s2.position.at(2))*(s1.velocity.at(2) - s2.velocity.at(2));
  double c =pow(s1.position.at(0)-s2.position.at(0),2)+ pow(s1.position.at(1)-s2.position.at(1),2)+ pow(s1.position.at(2)-s2.position.at(2),2) - pow(s1.radius+s2.radius,2);
  double d = pow(b,2)-4*a*c;
  if (dotproduct(subv(s1.velocity,s2.velocity),subv(s1.position,s2.position))>= 0){
    return -1;
  }
  if (a==0){
    return -1;
  }
  double t1 = (-b + sqrt(d))/(2*a);
  double t2 = (-b - sqrt(d))/(2*a);
  return min(t1,t2);
}

double predictwall(spheres s1){
  double a = pow(s1.velocity.at(0),2)+ pow(s1.velocity.at(1),2)+ pow(s1.velocity.at(2),2);
  double b = 2*s1.position.at(0)*s1.velocity.at(0)+ 2*(s1.position.at(1))*(s1.velocity.at(1))+ 2*(s1.position.at(2))*(s1.velocity.at(2));
  double c =pow(s1.position.at(0),2)+ pow(s1.position.at(1),2)+ pow(s1.position.at(2),2)- pow(s1.container-s1.radius,2);
  double d = pow(b,2)-4*a*c;
  if (a==0){
    return -1;
  }
  if (d>=0){
    double t1 = (-b + sqrt(d))/(2*a);
    double t2 = (-b - sqrt(d))/(2*a);
    return max(t1,t2);
  }
  return(-1);
}

vector<double> mulnv(vector<double> a,double b){
  std::vector<double> v;
  v.push_back(a.at(0)*b);
  v.push_back(a.at(1)*b);
  v.push_back(a.at(2)*b);
  return v;
}

vector<double> divnv(vector<double> a,double b){
  std::vector<double> v;
  v.push_back(a.at(0)/b);
  v.push_back(a.at(1)/b);
  v.push_back(a.at(2)/b);
  return v;
}


vector<double> changev(spheres s1,spheres s2){
  double m = (2*s2.mass)/(s1.mass + s2.mass);
  vector<double> v = subv(s1.velocity,s2.velocity);
  vector<double> c = subv(s1.position,s2.position);
  vector<double> newvelocity = subv(s1.velocity,mulnv(c,dotproduct(v,c)*m/(dotproduct(c,c))));
  return newvelocity;
}

vector<double> wallchange(spheres s1){
  double distance = sqrt(pow(s1.position.at(0),2)+pow(s1.position.at(1),2) + pow(s1.position.at(2),2));
  vector<double> unit = divnv(s1.position,distance);
  vector<double> sproject = mulnv(unit,dotproduct(s1.velocity,unit));
  std::vector<double> soth = subv(s1.velocity,sproject);
  vector<double> newvelocity = subv(soth,sproject);
  return newvelocity;
}


int main(int argc,char** argv){
  std::vector<double> twoballs;
  std::vector<double> cwall;
  double container = stoi(*(argv+1));
  int collision = stoi(*(argv+2));
  std::vector<spheres> spheresname;
  double mass,rad,p1,p2,p3,v1,v2,v3;
  string name,i;
  while (cin >> mass >> rad >> p1 >> p2 >> p3 >> v1 >> v2 >> v3 >> name){
    i = name;
    spheres name;
    name.mass = mass;
    name.radius = rad;
    name.velocity.push_back(v1);
    name.velocity.push_back(v2);
    name.velocity.push_back(v3);
    name.position.push_back(p1);
    name.position.push_back(p2);
    name.position.push_back(p3);
    name.name = i;
    name.container = container;
    name.count = collision;
    spheresname.push_back(name);
  }
  double energy;
  vector<double> momentum;
  momentum.push_back(0);
  momentum.push_back(0);
  momentum.push_back(0);
  for(int i = 0; i != spheresname.size(); i++){
    energy += 0.5* spheresname.at(i).mass*(pow(spheresname.at(i).velocity.at(0),2)+pow(spheresname.at(i).velocity.at(1),2)+pow(spheresname.at(i).velocity.at(2),2));
    momentum.at(0) += spheresname.at(i).velocity.at(0)*spheresname.at(i).mass;
    momentum.at(1) += spheresname.at(i).velocity.at(1)*spheresname.at(i).mass;
    momentum.at(2) += spheresname.at(i).velocity.at(2)*spheresname.at(i).mass;
  }
  cout << " here are the initial sphere " << endl;
  int c = 0 ;
  for(int i = 0; i != spheresname.size(); i++){
    c = collision - spheresname.at(i).count;
    cout << spheresname.at(i).name << " m = " << spheresname.at(i).mass << " r = "<< spheresname.at(i).radius <<" p = "<<'('<<spheresname.at(i).position.at(0)<<','<<spheresname.at(i).position.at(1)<<','<<spheresname.at(i).position.at(2)<<')'<<" v = "<<'('<<spheresname.at(i).velocity.at(0)<<','<<spheresname.at(i).velocity.at(1)<<','<<spheresname.at(i).velocity.at(2)<<')'<<"bounce = "<< c <<endl;
  }
  cout <<" energy = " << energy<<endl;
  cout << " momentum = " <<'('<< momentum.at(0)<<','<<momentum.at(1)<<','<<momentum.at(2)<<')'<<endl;
  double sumtime = 0.0;
  double time,wall;
  int sphere0,sphere1,sphere2;
  while (spheresname.size()>0){
    twoballs.clear();
    cwall.clear();
    double mintime = 1.7976931348623157e+308;
    for (int i= 0; i<spheresname.size();i++){
      time = predictwall(spheresname.at(i));
      if (time == mintime){
        cwall.push_back(i);
      }
      if ((time < mintime)&& (time > 0)){
        mintime = time;
        sphere0 = i;
        wall = mintime;
      }
    }
    mintime = 1.7976931348623157e+308;
    if (spheresname.size()>1){
      for (int i = 0; i<spheresname.size()-1;i++ ){
        for (int j = i+1; j<spheresname.size();j++){
          time = predict(spheresname.at(i),spheresname.at(j));
          if ((time > 0) && (time < mintime)){
            mintime = time;
            sphere1 = i;
            sphere2 = j;
          }
        } 
      }
    }
    std::vector<double> mm;
    spheres temp;
    if (mintime < wall){
      for(int i = 0; i < spheresname.size();i++){
        mm = addv(mulnv(spheresname.at(i).velocity,mintime),spheresname.at(i).position);
        spheresname.at(i).position = mm;
      }
      spheresname.at(sphere1).count -= 1;
      spheresname.at(sphere2).count -= 1;
      temp = spheresname.at(sphere1);
      spheresname.at(sphere1).velocity = changev(spheresname.at(sphere1),spheresname.at(sphere2));
      spheresname.at(sphere2).velocity = changev(spheresname.at(sphere2),temp);
      sumtime += mintime;
      energy = 0;
      momentum.at(0)=0;
      momentum.at(1)=0;
      momentum.at(2)=0;
      for(int i = 0; i != spheresname.size(); i++){
        energy += 0.5* spheresname.at(i).mass*(pow(spheresname.at(i).velocity.at(0),2)+pow(spheresname.at(i).velocity.at(1),2)+pow(spheresname.at(i).velocity.at(2),2));
        momentum.at(0) += spheresname.at(i).velocity.at(0)*spheresname.at(i).mass;
        momentum.at(1) += spheresname.at(i).velocity.at(1)*spheresname.at(i).mass;
        momentum.at(2) += spheresname.at(i).velocity.at(2)*spheresname.at(i).mass;
      }
      if (spheresname.at(sphere2).count > -1 || spheresname.at(sphere1).count > -1){
        cout << " time of event " << sumtime << endl;
        cout <<" colliding " << spheresname.at(sphere1).name <<" " <<spheresname.at(sphere2).name << endl;
        for(int i = 0; i != spheresname.size(); i++){
          cout << spheresname.at(i).name << " m = " << spheresname.at(i).mass << " r = "<< spheresname.at(i).radius <<" p = "<<'('<<spheresname.at(i).position.at(0)<<','<<spheresname.at(i).position.at(1)<<','<<spheresname.at(i).position.at(2)<<')'<<" v = "<<'('<<spheresname.at(i).velocity.at(0)<<','<<spheresname.at(i).velocity.at(1)<<','<<spheresname.at(i).velocity.at(2)<<')'<<"bounce = "<< c <<endl;
        }        
        cout <<" energy" << energy << endl;
        cout << " momentum = " <<'('<< momentum.at(0)<<','<<momentum.at(1)<<','<<momentum.at(2)<<')'<<endl;
      }
    }
    else{
      for(int i = 0; i < spheresname.size();i++){
        mm = addv(mulnv(spheresname.at(i).velocity,wall),spheresname.at(i).position);
        spheresname.at(i).position = mm;
      }
      spheresname.at(sphere0).count -= 1;
      spheresname.at(sphere0).velocity = wallchange(spheresname.at(sphere0));
      sumtime += wall;
      energy = 0;
      momentum.at(0)=0;
      momentum.at(1)=0;
      momentum.at(2)=0;
      for(int i = 0; i != spheresname.size(); i++){
        energy += 0.5* spheresname.at(i).mass*(pow(spheresname.at(i).velocity.at(0),2)+pow(spheresname.at(i).velocity.at(1),2)+pow(spheresname.at(i).velocity.at(2),2));
        momentum.at(0) += spheresname.at(i).velocity.at(0)*spheresname.at(i).mass;
        momentum.at(1) += spheresname.at(i).velocity.at(1)*spheresname.at(i).mass;
        momentum.at(2) += spheresname.at(i).velocity.at(2)*spheresname.at(i).mass;
      }
      if (spheresname.at(sphere0).count > -1){
        cout << " time of event "<< sumtime << endl;
        cout <<" colliding " << spheresname.at(sphere0).name<< endl;
        for(int i = 0; i != spheresname.size(); i++){
          int count = collision;
          cout << spheresname.at(i).name << " m = " << spheresname.at(i).mass << " r = "<< spheresname.at(i).radius <<" p = "<<'('<<spheresname.at(i).position.at(0)<<','<<spheresname.at(i).position.at(1)<<','<<spheresname.at(i).position.at(2)<<')'<<" v = "<<'('<<spheresname.at(i).velocity.at(0)<<','<<spheresname.at(i).velocity.at(1)<<','<<spheresname.at(i).velocity.at(2)<<')'<<"bounce = "<< c <<endl;
        }  
        cout <<" energy " << energy << endl;
        cout << " momentum = " <<'('<< momentum.at(0)<<','<<momentum.at(1)<<','<<momentum.at(2)<<')'<<endl;
      }
      else{
        spheresname.erase(spheresname.begin()+sphere0);
      }
    for(int i = 0; i < spheresname.size();i++){
      if (spheresname.at(i).count < 0){
        spheresname.erase(spheresname.begin()+i);
      }
    }
    }
  int stop = 0;
  for(int i = 0; i != spheresname.size(); i++){
    if (spheresname.at(i).velocity.at(0)==0 && spheresname.at(i).velocity.at(0)==0 && spheresname.at(i).velocity.at(0)==0){
      stop++;
    }
  if (stop == spheresname.size()){
    break;
  }
  }
}
}
