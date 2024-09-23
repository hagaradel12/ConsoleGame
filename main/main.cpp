#include <iostream>
#include <string>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include<ostream>
using namespace std;
#include "Object.h"
#include "Character.h"
#include "Hero.h"
#include "MedicHero.h"
#include "DemolitionHero.h"
#include "Monster.h"
#include "TankMonster.h"
#include "GhostMonster.h"
#include "Gun.h"
#include "Pistol.h"
#include "Bazooka.h"
#include "Riffle.h"
#include "Game.h"
#include "Potion.h"
#include "Ammo.h"
#include "Item.h"
#include <stdlib.h>
#include <iostream>
#include <conio.h>
int Game::round;
 //Object class implementation
void Object::setType(char type){
     this->type=type;
}
  char Object:: getType(){
    return type;
}
  Object:: Object(char type){
      this->type=type;
}
   Object::Object(){}
  Object:: ~Object(){}

  //MileStone2 operator<<
    ostream& operator<<(ostream& os,  const Object& obj){
      switch(obj.type){
           case 'T': os<<"Type: Tank Monster"<<endl;break;
           case 'G': os<<"Type: Ghost Monster"<<endl;break;
           case 'A': os<<"Type: Ammo"<<endl;break;
           case 'P': os<<"Type: Potion"<<endl;break;
           case 'D': os<<"Type: Demolition Hero"<<endl; cout<<(DemolitionHero&)obj<<endl;break;
           case 'M': os<<"Type: Medic Hero"<<endl; cout<<(MedicHero&)obj<<endl; break;


        }
return os;


  }

  //Character class implementation

   void  Character:: setHealthPoints(int healthPoints){
   this->healthPoints=healthPoints;
   }
   int  Character::  getHealthPoints(){
     return healthPoints;
   }
    Character:: Character(char type, Position *position, int healthPoints):Object(type){
   this->position=position;
   this->healthPoints=healthPoints;
   }
   Position* Character::getPosition(){
          return this->position;
}
   void Character::setPosition(int x, int y){
          Position* p=new Position(x,y);
          this->position=p;
   }

    Character:: Character(){}
    Character:: ~Character(){}

   //Hero class implementation
  void Hero:: setGun(Gun *gun){
  this->gun=gun;
  }
   Gun* Hero:: getGun(){
    return gun;
   }
       void Hero::useSpecial(){
       cout<<"hello"<<endl;
      }
   Hero:: Hero(char type, Position *position, int healthPoints, Gun *gun):Character(type, position, healthPoints){
        this->gun=gun;
   }
    Hero::Hero(){}
   Hero::~Hero(){}

Hero* Hero::operator+(Potion *p){
       this->setHealthPoints(this->getHealthPoints()+p->gethealing_amount());
       return this;
    }
   //MileStone2  operator+(Hero+Ammo)

   Hero* Hero::operator+(Ammo* ammo){
       //cout<<"num :"<<  ammo.getNo_of_bullets() ;
   if(this->getType() == 'D'){
        (((DemolitionHero*)this)->getGun2())->setNoOfbullets((((DemolitionHero*)this)->getGun2())->getNoOfbullets()+ammo->getNo_of_bullets());
   }
   else{
       this->getGun()->setNoOfbullets(this->getGun()->getNoOfbullets()+ammo->getNo_of_bullets());
   }
    return this;
   }



Hero* Hero:: operator-(Monster* m){
       this->setHealthPoints((this->getHealthPoints())-10);
     //check if tank monster
     if (m->getType()=='T'){
        int damageshild=((TankMonster *)m)->getShild()-20;
        if (damageshild<0){
            m->setHealthPoints(m->getHealthPoints()+damageshild);
           ((TankMonster *)m)->setShild(0);
        }
        else
           ((TankMonster *)m)->setShild(damageshild);
     }
        else
         m->setHealthPoints(m->getHealthPoints()-20);
    return this;
   }


   //MedicHero class implementation
   void  MedicHero::setHealingAmount(int healingAmount){
   this->healingAmount=healingAmount;
   }
    int MedicHero:: getHealingAmount(){
    return healingAmount;
    }
    MedicHero:: MedicHero(char type, Position* position, int healthPoints, Gun *gun, int healingAmount):Hero(type, position, healthPoints, gun){
      this->healingAmount=healingAmount;
      this->healOnce = false;
    }
     MedicHero:: MedicHero(){}
     MedicHero::~MedicHero(){}

    ostream& operator<<(ostream& os,  MedicHero& h){
         os<<"HP: "<< h.getHealthPoints()<<endl;
         os<<"Healing amount: "<<h.healingAmount<<endl;
         Gun g=*(h.getGun());
         os<<"Gun: "<<g<<endl;   //call the << operator in gun to get gun details
         return os;
     }

     void MedicHero::useSpecial(){

         if(healOnce==true){
            cout<<"you are only allowed to use your special ability once"<<endl;
         }
         else{
            healOnce = true;
            this->setHealthPoints(this->healingAmount+this->getHealthPoints());
         }

     }

    //DemolitionHero class implementation
     void DemolitionHero::setGun2(Gun* gun2){
       this->gun2=gun2;
     }
    Gun* DemolitionHero:: getGun2(){
       return gun2;
    }
   DemolitionHero:: DemolitionHero(char type, Position *position, int healthPoints, Gun *gun, Gun *gun2):Hero(type, position, healthPoints, gun){
        this->gun2=gun2;
    }
   DemolitionHero:: DemolitionHero(){}
   DemolitionHero:: ~DemolitionHero(){}

   ostream& operator<<(ostream& os, DemolitionHero& h){
         os<<"HP: "<< h.getHealthPoints()<<endl;
         Gun g=*(h.getcurrentGun());
         os<<"Current Gun: "<<g<<endl;
         return os;
     }
     void DemolitionHero::setcurrentGun(Gun *currentGun){
           this->currentGun=currentGun;
     }
     Gun* DemolitionHero::getcurrentGun(){
            return this->currentGun;
     }
     void DemolitionHero::useSpecial(){
        if (currentGun==gun2)
            currentGun=getGun();
        else
            currentGun=gun2;
     }


   //Monster Class implementation
  Monster:: Monster(char type, Position *position, int healthPoints, string name):Character(type, position, healthPoints){
      this-> name=name;
   }
  Monster::  Monster(){}
   Monster:: ~Monster(){}
  void Monster::setName(string name){
       this->name=name;
   }

  string Monster:: getName(){
       return name;
   }


   //GhostMonster class implementation
   GhostMonster:: GhostMonster(char type, Position *position, int healthPoints, string name, bool isVisble):Monster(type,position,healthPoints,name)
   {
    this-> isVisble=isVisble;
    }
    GhostMonster:: GhostMonster(){}
    GhostMonster:: ~GhostMonster(){}
     void GhostMonster:: setIsVisible( bool isVisble)
    {
    this-> isVisble=isVisble;
    }
     bool GhostMonster::getIsVisible()
    {
        return isVisble;
    }

    //TankMonster class implementation
    TankMonster:: TankMonster(char type, Position *position, int healthPoints, string name, int shild):Monster(type,position,healthPoints,name)
   {
    this-> shild= shild;
    }
    TankMonster:: TankMonster(){}
    TankMonster:: ~TankMonster(){}
    void TankMonster:: setShild( int  shild)
    {
    this-> shild= shild;
    }
   int TankMonster:: getShild()
    {
        return shild;
    }

    //Item class implementation
    Item:: Item(char type):Object(type){}
    Item:: Item(){}
    Item:: ~Item(){}

    //Ammo class implementation
    Ammo::Ammo(char type, int no_of_bullets): Item(type)
    {
        this-> no_of_bullets=no_of_bullets;
    }
   Ammo::Ammo(){}
   Ammo:: ~Ammo(){}
   void Ammo::setNo_of_bullets(int no_of_bullets){
     this-> no_of_bullets=no_of_bullets;
   }
  int  Ammo::  getNo_of_bullets()
   {
      return no_of_bullets;
   }

    //Potion class implementation
    Potion:: Potion(char type, int healing_amount): Item(type)
    {
        this->healing_amount=healing_amount;
    }
    Potion:: Potion(){}
    Potion:: ~Potion(){}
    void Potion:: setHealing_amount(int healing_amount)
     {
         this->healing_amount=healing_amount;
     }
     int Potion:: gethealing_amount()
     {
         return healing_amount;
     }
     Position::~Position(){}
     Position::Position(){}

     //Gun class implementation
     Gun:: Gun(char type,int noOfbullets, int damageAmount, int range,string name):Object(type)
     {
         this->name=name;
         this-> noOfbullets=noOfbullets;
         this->damageAmount=damageAmount;
         this->range=range;
     }
     void Gun::useSpecial(Hero& h1 , Object* map[15][15]){
       cout<<"hi"<<endl;
     }
     Gun:: Gun(){}
     Gun:: ~Gun(){}
     string Gun::  getName()
     {
         return name;
     }
     void Gun:: setName(string name)
     {
         this->name=name;
     }
     int Gun:: getDamageAmount()
     {
         return damageAmount;
     }
    void Gun:: setDamageAmount(int damageAmount)
     {
         this->damageAmount=damageAmount;
     }
     int Gun:: getNoOfbullets()
     {
         return noOfbullets;
     }
     void Gun:: setNoOfbullets(int noOfbullets)
     {
          this-> noOfbullets= noOfbullets;
     }
     int Gun:: getRange()
     {
         return range;
     }
     void Gun:: setRange(int range)
     {
          this-> range= range;
     }
     Position::Position(int x, int y){
        this->x=x;
        this->y=y;
     }
    int Position::getX(){
        return this->x;
    }
     int Position::getY(){
        return this->y;
    }
    void Position::setPosition(int x, int y){
        this->x=x;
        this->y=y;

    }


     ostream& operator<<( ostream& os ,  Gun& g )
     {
          os <<"Name: "<<g.name<<endl;
          os<<"Number of bullets: "<<g.noOfbullets<<endl;
           os<<"Range: "<<g.range<<endl;
       return os ;
    }
    //Pistol class implementation

    Pistol::Pistol():Gun('p',16,2,30,"Pistol"){}
     Pistol::~Pistol(){}
      void Pistol:: useSpecial(Hero& h1 , Object* map[15][15]){
         if(this->getNoOfbullets()<4){
            cout<<"You do not have enough Ammo"<<endl;
            return;
        }
        //dmg=30
        int x = h1.getPosition()->getX();
        int y = h1.getPosition()->getY();
        int x1 = h1.getPosition()->getX();
        int y1 =  h1.getPosition()->getY();
          int r =0;
         //right
          if (x<14){
            this->setNoOfbullets(this->getNoOfbullets()-1);
            while(x1<15 && r<2){
            if(map[x1][y]->getType()=='T'|| map[x1][y]->getType()=='G'){
                     if (map[x1][y]->getType()=='T'){
                        TankMonster *t=(TankMonster*)map[x1][y];
                        int damageshild=t->getShild()-30;
                         if (damageshild<0){
                         t->setHealthPoints(t->getHealthPoints()+damageshild);
                         t->setShild(0);
                     }
                  else
                       t->setShild(damageshild);
                  }
               else{
                 GhostMonster *g=(GhostMonster *)map[x1][y];
                  g->setHealthPoints(g->getHealthPoints()-30);
               }
                x1++;
                r++;
            }
            }
            x1=x;
        }
        //left
         r=0;
        if(x>0){
            this->setNoOfbullets(this->getNoOfbullets()-1);
            while(x1>=0 && r<2){
            if(map[x1][y]->getType()=='T'|| map[x1][y]->getType()=='G'){
                        if (map[x1][y]->getType()=='T'){
                        TankMonster *t=(TankMonster *)map[x1][y];
                        int damageshild=t->getShild()-30;
                         if (damageshild<0){
                         t->setHealthPoints(t->getHealthPoints()+damageshild);
                         t->setShild(0);
                     }
                  else
                       t->setShild(damageshild);
                  }
                else{
                 GhostMonster *g=(GhostMonster *)map[x1][y];
                  g->setHealthPoints(g->getHealthPoints()-30);
               }
                x1--;
                r++;
            }
            }
            x1=x;
        }
        //up
         r =0;
        if(y<14){
            this->setNoOfbullets(this->getNoOfbullets()-1);
             while(y1<15 && r<2){
             if(map[x][y1]->getType()=='T'|| map[x][y1]->getType()=='G'){
                        if (map[x][y1]->getType()=='T'){
                        TankMonster *t=(TankMonster *)map[x][y1];
                        int damageshild=t->getShild()-30;
                         if (damageshild<0){
                         t->setHealthPoints(t->getHealthPoints()+damageshild);
                         t->setShild(0);
                     }
                  else
                       t->setShild(damageshild);
                  }
               else{
                 GhostMonster *g=(GhostMonster *)map[x1][y];
                  g->setHealthPoints(g->getHealthPoints()-30);
               }
             y1++;
             r++;
           }
           }
           y1 =y;
        }
        //down
       r =0;
      if(y>0){
           this->setNoOfbullets(this->getNoOfbullets()-1);
             while(y1>=0 && r<2){
             if(map[x][y1]->getType()=='T'|| map[x][y1]->getType()=='G'){
                    if (map[x][y1]->getType()=='T'){
                        TankMonster *t=(TankMonster *)map[x][y1];
                        int damageshild=t->getShild()-30;
                         if (damageshild<0){
                         t->setHealthPoints(t->getHealthPoints()+damageshild);
                         t->setShild(0);
                     }
                  else
                       t->setShild(damageshild);
                  }
                else{
                 GhostMonster *g=(GhostMonster *)map[x1][y];
                  g->setHealthPoints(g->getHealthPoints()-30);
               }
             y1--;
             r++;
           }
         y1=y;
        }
         Game::round++;
              }
      }

//Bazooka class implementation
 Bazooka::Bazooka():Gun('b',4,8,150,"Bazooka"){}

void Bazooka::useSpecial(Hero& h1 , Object* map[15][15]){
            int i = h1.getPosition()->getX();
            int j = h1.getPosition()->getY();
            if(!((i==j)||(i+j==14))){
               cout<<"You're not standing on a diagonal cell"<<endl;
               return;
                 //hero not in diagonal
            }
            Game::round++;
            if(i==j){
                for(i=0; i<15; i++){
                 for(j=0; i<15; j++){
                    if(i==j && (map[i][j]->getType()=='G'||map[i][j]->getType()=='T'))
                         ((Monster*)(map[i][j]))->setHealthPoints(0);
                   }
            }
            }
            else{
                for(i=0; i<15; i++){
                 for(j=0; i<15; j++){
                    if(i+j==14 && (map[i][j]->getType()=='G'||map[i][j]->getType()=='T'))
                       ((Monster*)(map[i][j]))->setHealthPoints(0);
                   }
             }   }
        }
Bazooka::~Bazooka(){}


//rifle class implementation


Riffle::Riffle():Gun('r',30,4,20,"Riffle"){}
Riffle::~Riffle(){}

void Riffle:: useSpecial(Hero& h1, Object* map[15][15]){
            Game::round++;
           /* Gun *g;
            if(h1.getType()=='M')
                g=h1.getGun();
            else
                g=((DemolitionHero&)(h1)).getcurrentGun();

            int numB=g->*/
            int r=this->getRange();
            int c=1;
            int x=h1.getPosition()->getX();
            int y=h1.getPosition()->getY();
            if (this->getNoOfbullets()>=3){
                 while (c<=r && y+c<14 && this->getNoOfbullets()>0){ //up
                   if(map[x][y+c]->getType()=='T' || map[x][y+c]->getType()=='G'){
                     if (map[x][y+c]->getType()=='T'){
                       int damageshild=(((TankMonster*)(map[x][y+c]))->getShild())-this->getDamageAmount();
                      if (damageshild<0){
                        ((TankMonster*)( map[x][y+c]))->setHealthPoints((((TankMonster*)(map[x][y+c]))->getHealthPoints())-damageshild);
                         ((TankMonster*)(map[x][y+c]))->setShild(0);
                       }
                  else
                          ((TankMonster*)(map[x][y+c]))->setShild(damageshild);
                   }
                   else
                   ((Monster*)(map[x][y+c]))->setHealthPoints((((Monster*)(map[x][y+c]))->getHealthPoints())-this->getDamageAmount());

                      c++;
                      this->setNoOfbullets(this->getNoOfbullets()-1);
                   }
                 }
                 c=1;
                while (c<=r && x+c<14 && this->getNoOfbullets()>0){//right
                   if(map[x+c][y]->getType()=='T' || map[x+c][y]->getType()=='G'){
                     if (map[x+c][y]->getType()=='T'){
                       int damageshild=(((TankMonster*)(map[x][y+c]))->getShild())-this->getDamageAmount();
                      if (damageshild<0){
                         ((TankMonster*)(map[x+c][y]))->setHealthPoints(((TankMonster*)(map[x+c][y]))->getHealthPoints()-damageshild);
                       ((TankMonster*)(map[x+c][y]))->setShild(0);
                       }
                  else
                        ((TankMonster*)(map[x+c][y]))->setShild(damageshild);
                   }
                   else
                    ((Monster*)(map[x+c][y]))->setHealthPoints(((Monster*)(map[x+c][y]))->getHealthPoints()-this->getDamageAmount());
                     c++;
                      this->setNoOfbullets(this->getNoOfbullets()-1);
                   }
                 }
                 c=1;
                 while (c<=r && x-c<14 && this->getNoOfbullets()>0){//left
                   if(map[x-c][y]->getType()=='T' || map[x-c][y]->getType()=='G'){
                     if (map[x-c][y]->getType()=='T'){
                       int damageshild=((TankMonster*)(map[x-c][y]))->getShild()-this->getDamageAmount();
                      if (damageshild<0){
                         ((TankMonster*)(map[x-c][y]))->setHealthPoints(((TankMonster*)(map[x-c][y]))->getHealthPoints()-damageshild);
                        ((TankMonster*)(map[x-c][y]))->setShild(0);
                       }
                  else
                         ((TankMonster*)(map[x-c][y]))->setShild(damageshild);
                   }
                   else
                    ((Monster*)(map[x-c][y]))->setHealthPoints(((Monster*)(map[x-c][y]))->getHealthPoints()-this->getDamageAmount());
                     c++;
                      this->setNoOfbullets(this->getNoOfbullets()-1);
                   }
                 }

            }
            cout<<"no enough ammo"<<endl;
         }

     //Game class implementation


    void Game::useGunSpecial(){
        Gun *g;
         int i = hero->getPosition()->getX();
         int j = hero->getPosition()->getY();
         //get gun
          if(hero->getType()=='M')
                g=(((MedicHero*)(hero))->getGun());
          else
                g=(((DemolitionHero*)(hero))->getcurrentGun());
        //pistol
        if(g->getType()=='p'){
        if(g->getNoOfbullets()>=4){
           g->useSpecial(*hero, Grid);
           return;
        }
           else{
            cout<<"no enough ammo"<<endl;
            return;
           }
        }
       //riffle
           if(g->getType()=='r'){
        if(g->getNoOfbullets()>=3){
           g->useSpecial(*hero, Grid);
            return;
        }
           else{
            cout<<"no enough ammo"<<endl;
            return;
           }
        }
         //bazooka
        if(i==j || i+j==14)
            g->useSpecial(*hero,Grid);
        else
            cout<<"you're not standing on a diagonal"<<endl;

}

void Game::FireGun(char direction){
        int range;
        int dmg;
       if(hero->getType()=='M'){
        MedicHero *m=(MedicHero*)hero;
        if((m->getGun())->getNoOfbullets()<1){
            cout<<"No enough ammo, at least one bullet is needed"<<endl;
            return;
         }
         else{
            (m->getGun())->setNoOfbullets((m->getGun())->getNoOfbullets()-1);
            range=m->getGun()->getRange();
            dmg=m->getGun()->getDamageAmount();

         }
         }
         else{
            DemolitionHero *d=(DemolitionHero*)hero;
            if((d->getcurrentGun())->getNoOfbullets()<1){
            cout<<"No enough ammo, at least one bullet is needed"<<endl;
            return;
         }
         else{
             (d->getcurrentGun())->setNoOfbullets((d->getcurrentGun())->getNoOfbullets()-1);
              range=d->getGun()->getRange();
              dmg=d->getGun()->getDamageAmount();
          }
    }
    int i=hero->getPosition()->getX();
    int j=hero->getPosition()->getY();
    int currI=hero->getPosition()->getX()+1;
    int currJ=hero->getPosition()->getY()+1;
      char d=toupper(direction);//'u'/'U' ..
    switch(d){
     case 'U':
           if(!(j<14)) {
            cout<<"You can't fire up since you there are no cells above"<<endl;
            return;
           }
           else{
               while(range>0 && currJ<15){
                    if(Grid[currI][currJ]->getType()=='G' || Grid[currI][currJ]->getType()=='T'){
                       if (Grid[currI][currJ]->getType()=='T'){
                          int damageshild=((((TankMonster*)(Grid[currI][currJ]))->getShild())-dmg);
                            if (damageshild<0){
                             ((TankMonster*)(Grid[currI][currJ]))->setHealthPoints(((TankMonster*)(Grid[currI][currJ]))->getHealthPoints()+damageshild);
                                  ((TankMonster*)(Grid[currI][currJ]))->setShild(0);
                              }
                           else
                               ((TankMonster*)(Grid[currI][currJ]))->setShild(damageshild);
                         }
                       else
                       ((Monster*)(Grid[currI][currJ]))->setHealthPoints(((Monster*)(Grid[currI][currJ]))->getHealthPoints()-dmg);
                       return;
                    }
                        range--;
                        currJ++;
               }
           }
           break;
       case 'D':
           if(!(i>0)) {
            cout<<"You can't fire down since you there are no cells below"<<endl;
            return;
           }
           else{
               while(range>0 && currI>0){
                    if(Grid[currI][currJ]->getType()=='G' || Grid[currI][currJ]->getType()=='T'){
                       if (Grid[currI][currJ]->getType()=='T'){
                          int damageshild=((((TankMonster*)(Grid[currI][currJ]))->getShild())-dmg);
                            if (damageshild<0){
                             ((TankMonster*)(Grid[currI][currJ]))->setHealthPoints(((TankMonster*)(Grid[currI][currJ]))->getHealthPoints()+damageshild);
                                  ((TankMonster*)(Grid[currI][currJ]))->setShild(0);
                              }
                           else
                               ((TankMonster*)(Grid[currI][currJ]))->setShild(damageshild);
                         }
                       else
                       ((Monster*)(Grid[currI][currJ]))->setHealthPoints(((Monster*)(Grid[currI][currJ]))->getHealthPoints()-dmg);
                       return;
                    }
                        range--;
                        currI--;
               }
           }
           break;
           case 'R':
           if(!(j<14)) {
            cout<<"You can't fire right since you are standing on the rightmost cell"<<endl;
            return;
           }
           else{
               while(range>0 && currJ<15){
                   if(Grid[currI][currJ]->getType()=='G' || Grid[currI][currJ]->getType()=='T'){
                       if (Grid[currI][currJ]->getType()=='T'){
                          int damageshild=((((TankMonster*)(Grid[currI][currJ]))->getShild())-dmg);
                            if (damageshild<0){
                             ((TankMonster*)(Grid[currI][currJ]))->setHealthPoints(((TankMonster*)(Grid[currI][currJ]))->getHealthPoints()+damageshild);
                                  ((TankMonster*)(Grid[currI][currJ]))->setShild(0);
                              }
                           else
                               ((TankMonster*)(Grid[currI][currJ]))->setShild(damageshild);
                         }
                       else
                       ((Monster*)(Grid[currI][currJ]))->setHealthPoints(((Monster*)(Grid[currI][currJ]))->getHealthPoints()-dmg);
                       return;
                    }
                        range--;
                        currJ++;
               }
           }
           break;
           case 'L':
           if(!(i>0)) {
            cout<<"You can't fire left since you are standing on the leftmost cell"<<endl;
            return;
           }
           else{
               while(range>0 && currJ>0){
                    if(Grid[currI][currJ]->getType()=='G' || Grid[currI][currJ]->getType()=='T'){
                       if (Grid[currI][currJ]->getType()=='T'){
                          int damageshild=((((TankMonster*)(Grid[currI][currJ]))->getShild())-dmg);
                            if (damageshild<0){
                             ((TankMonster*)(Grid[currI][currJ]))->setHealthPoints(((TankMonster*)(Grid[currI][currJ]))->getHealthPoints()+damageshild);
                                  ((TankMonster*)(Grid[currI][currJ]))->setShild(0);
                              }
                           else
                               ((TankMonster*)(Grid[currI][currJ]))->setShild(damageshild);
                         }
                       else
                       ((Monster*)(Grid[currI][currJ]))->setHealthPoints(((Monster*)(Grid[currI][currJ]))->getHealthPoints()-dmg);
                       return;
                    }
                        range--;
                        currJ--;
               }
           }
           break;
    }
    cout<<"No monsters found within gun range"<<endl;
  }
void Game::move(Hero* h1, char direction){
        int x=h1->getPosition()->getX();
        int y=h1->getPosition()->getY();
        char direction1=toupper(direction);
        char type=h1->getType();
        switch(direction1){//up x-1 y
         case 'U':
           if (x-1>=0){//check in borders
                round++;
            if (Grid[x-1][y]->getType()=='T' || Grid[x-1][y]->getType()=='G'){
                *h1-((Monster*)(Grid[x-1][y]));//typecast into monster not sure

            }
            else {
                if (Grid[x-1][y]->getType()=='A'){
                 h1=*h1+((Ammo*)(Grid[x-1][y])); //typecast into ammo not sure
                 Grid[x-1][y]=h1;
                 Grid[x-1][y]->setType(type);//move hero on grid
                  Grid[x][y]=new Object('N');
                 h1->setPosition(x-1,y);//move hero position

                }

            else {
                if (Grid[x-1][y]->getType()=='P'){
                h1=*h1+((Potion*)(Grid[x-1][y]));//typecast into ammo not sure
                 Grid[x-1][y]=h1;
                 Grid[x-1][y]->setType(type);//move hero on grid
                Grid[x][y]=new Object('N');
                 h1->setPosition(x-1,y);//move hero position
            }


            else { //moving to an empty cell
                 h1->setPosition(x-1,y);
                 Grid[x-1][y]->setType(type);//move hero on grid
                 Grid[x][y]=new Object('N');
                 Grid[x-1][y]=h1;
              }   //move hero position
            }
            }
          }

       break;
       case 'L'://left x y-1
          if (y-1>=0){//check in borders
                round++;
           if (Grid[x][y-1]->getType()=='T' || Grid[x][y-1]->getType()=='G'){
                h1=*h1-((Monster*)(Grid[x][y-1]));//typecast into monster not sure

            }
            else {
                if (Grid[x][y-1]->getType()=='A'){
                h1=*h1+((Ammo*)(Grid[x][y-1]));//typecast into ammo not sure
                 Grid[x-1][y]=h1;
                 Grid[x][y-1]->setType(type);//move hero on grid
                Grid[x][y]=new Object('N');
                 h1->setPosition(x,y-1);//move hero position
                }

            else {
                if (Grid[x][y-1]->getType()=='P'){
                 h1=*h1+((Potion*)(Grid[x][y-1]));//typecast into ammo not sure
                  Grid[x-1][y]=h1;
                 Grid[x][y-1]->setType(type);//move hero on grid
                  Grid[x][y]=new Object('N');
                 h1->setPosition(x,y-1);//move hero position
                }

            else { //moving to an empty cell
                 Grid[x][y-1]->setType(type);//move hero on grid
                 h1->setPosition(x,y-1);//move hero position
                  Grid[x][y]=new Object('N');
                 Grid[x][y-1]=h1;
            }
            }
          }
          }
          break;

      case'R'://right x y+1
          if (y+1<=14){//check in borders
                round++;
             if (Grid[x][y+1]->getType()=='T' || Grid[x][y+1]->getType()=='G'){
                h1=*h1-((Monster*)(Grid[x][y+1]));//typecast into monster not sure

            }
            else {
                if (Grid[x][y+1]->getType()=='A'){

                 *h1+((Ammo*)(Grid[x][y+1])); //typecast into ammo not sure
                  Grid[x][y+1]=h1;
                 Grid[x][y+1]->setType(type);//move hero on grid
                 Grid[x][y]=new Object('N');
                 h1->setPosition(x,y+1);//move hero position
                }

            else {
                if (Grid[x][y+1]->getType()=='P'){
                 *h1+((Potion*)(Grid[x][y+1]));//typecast into ammo not sure
                  Grid[x][y+1]=h1;
                 Grid[x][y+1]->setType(type);//move hero on grid
                  Grid[x][y]=new Object('N');
                 h1->setPosition(x,y+1);//move hero position
                }

            else { //moving to an empty cell
                 Grid[x][y+1]->setType(type);//move hero on grid
                 h1->setPosition(x,y+1);//move hero position
                  Grid[x][y+1]=h1;
                 Grid[x][y]=new Object('N');
                 Grid[x][y+1]=h1;
            }
            }
          }
          }
          break;

      case 'D'://down x+1 y
          if (x+1<=14){//check in borders
            round++;
            if (Grid[x+1][y]->getType()=='T' || Grid[x+1][y]->getType()=='G'){
               *h1-((Monster*)(Grid[x+1][y]));

            }
            else {
                if (Grid[x+1][y]->getType()=='A'){
                 *h1+((Ammo*)(Grid[x+1][y]));//typecast into ammo not sure
                  Grid[x+1][y]=h1;
                 Grid[x+1][y]->setType(type);//move hero on grid
                  Grid[x][y]=new Object('N');
                 h1->setPosition(x+1,y);//move hero position
            }

            else {
                if (Grid[x+1][y]->getType()=='P'){
                *h1+((Potion*)(Grid[x+1][y]));//typecast into ammo not sure
                  Grid[x+1][y]=h1;
                 Grid[x+1][y]->setType(type);//move hero on grid
                 Grid[x][y]=new Object('N');
                 h1->setPosition(x+1,y);//move hero position
            }


            else { //moving to an empty cell
                 Grid[x+1][y]->setType(type);//move hero on grid
                 h1->setPosition(x+1,y);//move hero position
                 Grid[x][y]=new Object('N');
                 Grid[x+1][y]=h1;
            }
            }
          }
          }
       break;
       default: cout<<"wrong input"<<endl;//should check here or not break;
        }

    }


void Game::GenerateMap(){
    round =0;
    srand((unsigned) time(NULL));
    int count;
    int rAmt;
  /*Grid=new Object*[15];
  for(int i=0; i<15; i++){
        Grid[i]=new Object[15];
  }*/
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
            Grid[i][j]=new Object('.');
            }
        }

  for(int i=0; i<15; i++){
      for(int j=0; j<15; j++){
       Grid[i][j]->setType('N');
      }
    }


  //5 health points randomly
 count=0;
 while(count<5 ){
     int randomI=rand()%15;
     int randomJ=rand()%15;
    while((randomI==0 && randomJ==0) || (Grid[randomI][randomJ]->getType()!='N') ){
       randomI=rand()%15;
       randomJ=rand()%15;
    }
    rAmt = (rand()%41)+10;
    Grid[randomI][randomJ]=new Potion('P', rAmt);
    count++;
 }
 //10 ammo
 count=0;
 while(count<10 ){
     int randomI=rand()%15;
    int randomJ=rand()%15;
    while((randomI==0 && randomJ==0) || (Grid[randomI][randomJ]->getType()!='N') ){
       randomI=rand()%15;
       randomJ=rand()%15;
    }
    rAmt = (rand()%16)+5;  //16: 0-15+5=5-20
    Grid[randomI][randomJ]=new Ammo('A', rAmt);
    count++;
 }
 //5 monsters ghost
 count=0;
 while(count<5 ){
    int randomI=rand()%15;
    int randomJ=rand()%15;
    while((randomI==0 && randomJ==0) || (Grid[randomI][randomJ]->getType()!='N') ){
       randomI=rand()%15;
       randomJ=rand()%15;
    }
    rAmt = ((rand()%10)+6)*10;  //10: 0-9+6=6-15
    Position* p=new Position(randomI,randomJ);
    Grid[randomI][randomJ]=new GhostMonster('G',p,rAmt,"y" ,true);
    count++;
 }
 //5 monsters tank
 count=0;
 while(count<5 ){
    int randomI=rand()%15;
    int randomJ=rand()%15;
   while((randomI==0 && randomJ==0) || (Grid[randomI][randomJ]->getType()!='N') ){
       randomI=rand()%15;
       randomJ=rand()%15;
    }
    rAmt = ((rand()%10)+6)*10;  //10: 0-9+6=6-15
    Position* p=new Position(randomI,randomJ);
    Grid[randomI][randomJ]=new TankMonster('T',p,rAmt,"x",20);
    count++;
 }


  }



  void Game:: showMap(){

    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
           if(Grid[i][j]->getType()=='N' || (Grid[i][j]->getType()=='G' && ((GhostMonster*)(Grid[i][j]))->getIsVisible()==false))
                cout<<".";
           else
            cout<<Grid[i][j]->getType();
           }
    cout<<endl;
    }

    }
   void Game::startGame(){
      int x,y;
      Gun *g1,*g2;
      Position *p=new Position(0,0);


      cout<< "Please enter 1 to choose Demolition or 2 to choose Medic" ;
      cin>>x;
      while(!(x>0 && x<3)){
           cout<< "Please enter 1 to choose Demolition or 2 to choose Medic" ;
           cin>>x;
      }
      if(x==1){
            cout<< "Choose your first weapon, Please enter 1 to choose Riffle, 2 to choose Bazooka, or 3 to choose Pistol";
      cin>>y;
      while(!(y>0 && y<4)){
           cout<< "Choose your first weapon, Please enter 1 to choose Riffle, 2 to choose Bazooka, or 3 to choose Pistol";
           cin>>y;
      }
     if(y==1)
        g1=new Riffle();
      if(y==2)
        g1=new Bazooka();
      else if(y==3){
        g1=new Pistol();
      }
        cout<< "Choose your second weapon, Please enter 1 to choose Riffle, 2 to choose Bazooka, or 3 to choose Pistol";
      cin>>y;
      while(!(y>0 && y<4)){
           cout<< "Choose your second weapon, Please enter 1 to choose Riffle, 2 to choose Bazooka, or 3 to choose Pistol";
           cin>>y;
      }
      if(y==1)
        g2=new Riffle();
      if(y==2)
        g2=new Bazooka();
      else if(y==3){
        g2=new Pistol();
      }

        hero=new DemolitionHero('D', p, 150,g1,g2 );
        ((DemolitionHero*)(hero))->setcurrentGun(g2);
      }
      else{

        cout<< "Please enter 1 to choose Riffle, 2 to choose Bazooka, or 3 to choose Pistol";
      cin>>y;
      while(!(y>0 && y<4)){
           cout<< "Please enter 1 to choose Riffle, 2 to choose Bazooka, or 3 to choose Pistol";
           cin>>y;
      }
      if(y==1)
        g2=new Riffle();
      if(y==2)
        g2=new Bazooka();
      else{
        g2=new Pistol();
      }
          hero=new MedicHero('M', p, 100,g2 ,50 );

    }

        GenerateMap();
        Grid[0][0]=hero;
        showMap();
        displayUI();

    }
    Game::Game(){
       startGame();
    }

    Game::~Game() {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                delete Grid[i][j];
            }
        }
    }



    void Game::displayUI(){
        char x;
        char d;
        while(checkGameOver()==-1){
        cout<<"Game Controls:"<<endl;
        cout<<"m to move"<<endl;
        cout<<"f to fire gun"<<endl;
        cout<<"g to use your gun's special ability, can be done once"<<endl;
        if(hero->getType()=='D')
        cout<<"s to swap guns"<<endl;
        else
        cout<<"h to heal, can be done once"<<endl;
        cin>>x;
        switch(x){
        case 'm':
            cout<<"Choose a direction to move"<<endl;
            cout<<"Directions: U, D, R, L, you can also use lower case letters"<<endl;
            cin>>d;
            move(hero, d);
            break;
        case 'f':
             cout<<"Choose a direction to fire"<<endl;
            cout<<"Directions: U, D, R, L, you can also use lower case letters"<<endl;
            cin>>d;
            FireGun(d);
            break;
        case 'g':
            useGunSpecial();
            break;
        case 's':
          if(hero->getType()=='M'){
             cout<<"incorrect input, please try again!"<<endl;
             break;
          }
          else{
           ((DemolitionHero*)hero)->useSpecial();
            break;
        }
        case 'h':
        if(hero->getType()=='D'){
             cout<<"incorrect input, please try again!"<<endl;
             break;
          }
          else{
            ((MedicHero*)hero)->useSpecial();
            break;
        }
        default:
            cout<<"incorrect input, please try again!"<<endl;
        }

        Game::updateMap();
    }
    if(checkGameOver()==0)
        cout<<"Game Over, Try again!"<<endl;
    else
         cout<<"Yay, You won!"<<endl;
    }

    int Game::checkGameOver(){
      if(hero->getHealthPoints()<=0){
      //  cout<<"Game Over"<<endl;
        return 0;
      }
        for(int i=0; i<15; i++){
            for(int j=0; j<15; j++){
                if(Grid[i][j]->getType()=='G' ||Grid[i][j]->getType()=='T'){
                 if (((Monster*)(Grid[i][j]))->getHealthPoints()>0)
                    return -1;
               }
              }
        }
    //    cout<<"You have won"<<endl;
        return 1;
    }
    void Game::updateMap(){
        bool isV;
        Position *p;
        int randomI;
        int randomJ;
        int rAmt;
       if(checkGameOver()==-1){
          for(int i=0; i<15; i++){
            for(int j=0; j<15; j++){
                if(Grid[i][j]->getType()=='G' ||Grid[i][j]->getType()=='T') {
                    if(Grid[i][j]->getType()=='T') {
                    if (((Monster*)(Grid[i][j]))->getHealthPoints()<=0)
                       Grid[i][j]=new Object('N');
              }}
            }
          }
            if(round%3==0 && !(round==0)){
                for(int i=0; i<15; i++){
                for(int j=0; j<15; j++){
                if(Grid[i][j]->getType()=='G'){
                   if(((GhostMonster*)(Grid[i][j]))->getIsVisible()==true)
                        ((GhostMonster*)(Grid[i][j]))->setIsVisible(false);
                   else
                      ((GhostMonster*)(Grid[i][j]))->setIsVisible(true);
                }
              }
            }
            }
        if(round%20==0 && round!=0){

    //1 monsters ghost
    randomI=rand()%15;
    randomJ=rand()%15;
    while((randomI==0 && randomJ==0) || (Grid[randomI][randomJ]->getType()!='N') ){
       randomI=rand()%15;
       randomJ=rand()%15;
    }
    rAmt = ((rand()%10)+6)*10;  //10: 0-9+6=6-15
     p=new Position(randomI,randomJ);
    if(round%6==0)
        isV=true;
        else
        isV=false;
    Grid[randomI][randomJ]=new GhostMonster('G',p,rAmt,"y" ,isV);
                //1 monsters tank

     randomI=rand()%15;
     randomJ=rand()%15;
   while((randomI==0 && randomJ==0) || (Grid[randomI][randomJ]->getType()!='N') ){
       randomI=rand()%15;
       randomJ=rand()%15;
    }
    rAmt = ((rand()%10)+6)*10;  //10: 0-9+6=6-15
     p=new Position(randomI,randomJ);
    Grid[randomI][randomJ]=new TankMonster('T',p,rAmt,"x",20);
            }
    //print and clear console
    //system("clear");
    cout<<*hero<<endl;
    cout<<Game::round<<endl;
    showMap();

    }
       }



int main()
{
    Game game;
    game.startGame();
 //  Game *g=new Game();
    return 0;
}


