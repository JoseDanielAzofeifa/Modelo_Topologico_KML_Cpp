/*
** Copyright © YYYY NAME
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Library General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/**
   @file main.cpp
   @author NAME
   @date YYYY-MM-DD
   @version 0.01
*/
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "tinyxml2\tinyxml2.h"
#include <sstream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include "creararch.cpp"
#include "psimpl.h"
using namespace std;
using namespace tinyxml2;
Fl_Double_Window *win;

int ver=0;

vector<double> geox;                                                         
vector<double> geoy;
vector<double> geox2;                                                         
vector<double> geoy2;
vector<double> geoxz;                                                         
vector<double> geoyz;
vector<double> geox2z;                                                         
vector<double> geoy2z;

vector<double> linx;                                                         
vector<double> liny;
vector<double> linx2;                                                         
vector<double> liny2;
vector<double> linxz;                                                         
vector<double> linyz;
vector<double> linx2z;                                                         
vector<double> liny2z;


vector<double> coordx;                                                         
vector<double> coordy;
vector<double> coordx2;                                                         
vector<double> coordy2;
vector<double> coordxz;
vector<double> coordxz2;                                                         
vector<double> coordyz;                                                         
vector<double> coordyz2;
vector<double> coordxsimp;                                                         
vector<double> coordysimp;
vector<double> coordx2simp;                                                         
vector<double> coordy2simp;
vector<double> bound;
vector<double> boundz;
vector<double> todox;
vector<double> todoy;
vector<double> todoxz;
vector<double> todoyz;
vector<double> linea;
vector<double> lineaz;
vector<int> orden;
vector<int>repetidos;
int cont;
unsigned tolerance = 25;    
bool paint=false,painttd=false,paintpnt=false,paintln=false,paintpol=false;
char *filenamepnt = "Points.pnt";
char *datopnt = " ";
char *filenameln = "Lines.ln";
char *datoln = " ";
char *filenamepol = "Poligons.pol";
char *datopol = " ";
char *filenamesimp= "Simplify.kml";
char *datosimp = " ";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dibujar
class MyCanvas : public Fl_Widget {
  void draw() {          
         if (paint==true){
         int a=0,q=0;
         fl_color(FL_WHITE);
         fl_rectf(x(),y(),w(),h());
         // DRAW
    double mayory2=coordy2[0];
    double menorx=coordx[0];
    for(int i=0; i<coordx.size();i++) {
            if (mayory2<coordy2[i])
               mayory2=coordy2[i];
            if (menorx>coordx[i])
               menorx=coordx[i];                    
         }
    bound.push_back (menorx);  
    bound.push_back (mayory2);
    redraw();
    
    if (painttd==true){                                       //todo
         fl_color(FL_BLACK);
         for(int i=0; i<coordx.size();i++) {                      
                       int x1 = 100+((int)((coordx[i]-bound[0])*100000))/10;
                       int y1 = 100+((int)((bound[1]-coordy[i])*100000))/10;
                       int x2 = 100+((int)((coordx2[i]-bound[0])*100000))/10;
                       int y2 = 100+((int)((bound[1]-coordy2[i])*100000))/10;
                    fl_line(x1,y1,x2,y2); 
         }
    }
    
    if(paintln==true){                                              //lineas
         fl_color(FL_DARK_GREEN);
         for(int i=0; i<linx.size();i++) {                       
                       int lx1 = 100+((int)((linx[i]-bound[0])*100000))/10;
                       int ly1 = 100+((int)((bound[1]-liny[i])*100000))/10;
                       int lx2 = 100+((int)((linx2[i]-bound[0])*100000))/10;
                       int ly2 = 100+((int)((bound[1]-liny2[i])*100000))/10;
                    fl_line(lx1,ly1,lx2,ly2);                   
         }
       }  
       
    if(paintpol==true){                                               //poligono
         fl_color(FL_BLUE);
         for(int i=0; i<geox.size();i++) {                       
                       int gx1 = 100+((int)((geox[i]-bound[0])*100000))/10;
                       int gy1 = 100+((int)((bound[1]-geoy[i])*100000))/10;
                       int gx2 = 100+((int)((geox2[i]-bound[0])*100000))/10;
                       int gy2 = 100+((int)((bound[1]-geoy2[i])*100000))/10;
                    fl_line(gx1,gy1,gx2,gy2);                   
         }
       }        
    if (paintpnt==true){                                      //puntos
      fl_color(FL_RED);
      for(int r=0;r<todox.size();r++){
       for(int s=0;s<todoy.size();s++){
          if(r!=s && todox[r]==todox[s] && todoy[r]==todoy[s])
          {
             todox.erase(todox.begin()+s);
             todoy.erase(todoy.begin()+s);
          }
       }
     }
     for(int z=0;z<todox.size();z++){
             int x = 100+((int)((todox[z]-bound[0])*100000))/10;
             int y = 100+((int)((bound[1]-todoy[z])*100000))/10;
             fl_point(x,y);  
     }
    }
    
   }          
  }
  static void Canvas_CB(void *userdata) {
        MyCanvas *o = (MyCanvas*)userdata;
        o->redraw();
        Fl::repeat_timeout(0.1, Canvas_CB, userdata);}
        
public: 
     MyCanvas(int X,int Y,int W,int H,const char*L=0) : Fl_Widget(X,Y,W,H,L) {
     Fl::add_timeout(0.1, Canvas_CB, (void*)this);}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dibujar puntos
void pntdoc(Fl_Widget* buttonptr){
     painttd=true;
     paintpnt=true;
     paintln=false;
     paintpol=false;
     }
     
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dibujar lineas
void lndoc(Fl_Widget* buttonptr){
     painttd=true;
     paintpnt=false;
     paintln=true;
     paintpol=false;
     }
     
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dibujar poligonos
void poldoc(Fl_Widget* buttonptr){
     painttd=true;
     paintpnt=false;
     paintln=false;
     paintpol=true;
     }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dibujar todo
void tddoc(Fl_Widget* buttonptr){
     painttd=true;
     paintln=true;
     paintpol=true;
     paintpnt=true;
     }
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//crear doc puntos
void createdoc(Fl_Widget* buttonptr){
     try{
         
    string datospnt="";
    for(int i=0;i<todox.size();i++){
        ostringstream sstream;
        sstream << todox[i];
        string puntosx = sstream.str();
        ostringstream sstreama;
        sstreama << todoy[i];
        string puntosy = sstreama.str();
    datospnt+=puntosx+","+puntosy+"\n";}
    char *datapnt=new char[datospnt.length() + 1];     
   	strcpy(datapnt, datospnt.c_str());
   	datopnt=datapnt;
   	creararch archivopnt;
    archivopnt.crearArchivo(filenamepnt,datopnt);
          
     Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Points created");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	
	string datosln="";                              //lineas
    for(int i=0;i<linx.size();i++){
        ostringstream sstream;
        sstream << linx[i];
        string linx = sstream.str();
        ostringstream sstreama;
        sstreama << liny[i];
        string liny = sstreama.str();
        ostringstream sstream2;
        sstream2 << linx2[i];
        string linx2 = sstream2.str();
        ostringstream sstreama2;
        sstreama2 << liny2[i];
        string liny2 = sstreama2.str();
    datosln+=linx+","+liny+" "+linx2+","+liny2+"\n";}
    char *dataln=new char[datosln.length() + 1];     
   	strcpy(dataln, datosln.c_str());
   	datoln=dataln;
   	creararch archivoln;
    archivoln.crearArchivo(filenameln,datoln);
    
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Lines created");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	
	string datospol="";                              //poligonos
    for(int i=0;i<geox.size();i++){
        ostringstream sstream;
        sstream << geox[i];
        string geox = sstream.str();
        ostringstream sstreama;
        sstreama << geoy[i];
        string geoy = sstreama.str();
        ostringstream sstream2;
        sstream2 << geox2[i];
        string geox2 = sstream2.str();
        ostringstream sstreama2;
        sstreama2 << geoy2[i];
        string geoy2 = sstreama2.str();
    datospol+=geox+","+geoy+" "+geox2+","+geoy2+"\n";}
    char *datapol=new char[datospol.length() + 1];     
   	strcpy(datapol, datospol.c_str());
   	datopol=datapol;
   	creararch archivopol;
    archivopol.crearArchivo(filenamepol,datopol);
     
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Poligons created");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();}
	catch(...){
     Fl_Window *window;
	 Fl_Box *box;
	 window = new Fl_Window(300, 180);
	 box = new Fl_Box(20, 40, 260, 100, "FILE ERROR");
	 box->box(FL_UP_BOX);
	 box->labelsize(24);
	 box->labelfont(FL_BOLD+FL_ITALIC);
	 box->labeltype(FL_SHADOW_LABEL);
	 window->end();
	 window->show();   
     }
     }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//saca las coordenadas
void sacarcoor(string s, bool isGeo)
{
    char * pch;
    istringstream iss(s);
    string sub;
    bool i=false;
    double x1=0;
    double x2=0;
    double y1=0;
    double y2=0;
    int tam=0;
    int locate=0;
    do
    {
        string sub;
        iss >> sub;
        cout<<sub<< endl;
        tam = sub.size();
        if (tam>0)
        {
            if (x1==0 && y1==0)
            {
               x1 = strtof (sub.c_str(),NULL);
               pch=strchr(sub.c_str(),',');
               locate = pch-sub.c_str()+1;
               string subcadenay = sub.substr(locate);
               y1 = strtof (subcadenay.c_str(),NULL);
            }
            else
            {
                if (i)
                {
                   x1=x2;
                   y1=y2;
                }
                i=true;
               x2 = strtof (sub.c_str(),NULL);
               pch=strchr(sub.c_str(),',');
               locate = pch-sub.c_str()+1;
               string subcadenay = sub.substr(locate);
               y2 = strtof (subcadenay.c_str(),NULL);
               if (isGeo)
               {
                         geox.push_back (x1);                                                         
                         geoy.push_back (y1);
                         geox2.push_back (x2);                                                          
                         geoy2.push_back (y2); 
               }
               else
               {
                         linx.push_back (x1);                                                         
                         liny.push_back (y1);
                         linx2.push_back (x2);                                                          
                         liny2.push_back (y2); 
               }
                   coordx.push_back (x1);  
                   coordy.push_back (y1);    
                   coordx2.push_back (x2);  
                   coordy2.push_back (y2); 
                   todox.push_back (x1);  
                   todoy.push_back (y1);    
                   todox.push_back (x2);  
                   todoy.push_back (y2);
            }
        }
    }while (iss);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//leer kml
void leer(const char * archivo)
 {      
        int contador=0;
        const char* itemText="";
  try{
        XMLDocument doc;
        doc.LoadFile(archivo);
        
 		XMLElement* itemElement = doc.FirstChildElement( "kml" )->FirstChildElement( "Document" )->FirstChildElement( "Folder" )->FirstChildElement( "Placemark");
        while(itemElement){
            if(contador>=766 && contador<=772 || contador>=774 && contador<788 || contador>791 && contador<796 || contador>796 && contador<800 || contador>800 && contador<815 || contador>815 && contador<829 || contador>829 && contador<832 || contador>833 && contador<=834){
                   XMLElement* itemElement2 = itemElement->FirstChildElement( "MultiGeometry" )->FirstChildElement( "LineString" );
                  while(itemElement2){
                        XMLElement* itemElementcoor2 = itemElement2->FirstChildElement( "coordinates" );
                        itemText = itemElementcoor2->GetText();
                        sacarcoor(itemText,true);
                        itemElement2 = itemElement2->NextSiblingElement("LineString");
                        }
            }
             else{
                  XMLElement* itemElementcoor = itemElement->FirstChildElement( "LineString" )->FirstChildElement( "coordinates" );
                  itemText = itemElementcoor->GetText();
                  sacarcoor(itemText, false);
            }
	        contador++;
            itemElement = itemElement->NextSiblingElement("Placemark");
       }
                 
    coordxz=coordx;
    coordxz2=coordx2;
    coordyz=coordy;
    coordyz2=coordy2;
    boundz=bound;
    todoxz=todox;
    todoyz=todoy;
    linxz=linx;
    linx2z=linx2;
    linyz=liny;
    liny2z=liny2;
    geoxz=geox;
    geox2z=geox2;
    geoyz=geoy;
    geoy2z=geoy2;
    paint=true;                                               
    painttd=true;
    Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "File loaded");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
  }
  catch(...) {
    Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "File error");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//open.cpp 
void read_cb( Fl_Widget* o , void* ) {
    try{
   Fl_Button* b=(Fl_Button*)o;
   Fl_Input* iw = (Fl_Input*) b -> parent() -> child(1);
   leer(iw->value() );}
   catch(...){
    Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "File error");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();}
}



void open_window(Fl_Widget* buttonptr) {
   try{
   Fl_Window* win= new Fl_Window(420,200, "OPEN FILE");
   win->begin();      
      Fl_Button*  copy = new Fl_Button( 10, 150, 70, 30, "OPEN"); //child 0   : 1st widget
      Fl_Input*       inp = new Fl_Input(50, 50, 350, 30, "FILE");              //child 1 : 2rd widget
      Fl_Input*       msj = new Fl_Input(300, 20, 0, 0, "Example: C:\\\\Documents\\\\text.kml");
   win->end();
   copy->callback(  read_cb );
   win->show();}
   catch(...){
   Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Open error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();}
 }
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dibujar documento.cpp 
void doc_window(Fl_Widget* buttonptr) {
   try{
   Fl_Window* win= new Fl_Window(700,100, "DRAW DOC");
   win->begin();      
      Fl_Button*  drawpnt = new Fl_Button( 10, 30, 150, 30, "POINTS DOCUMENT"); 
      Fl_Button*  drawln = new Fl_Button( 170, 30, 150, 30, "LINES DOCUMENT"); 
      Fl_Button*  drawpol = new Fl_Button( 340, 30, 175, 30, "POLIGONS DOCUMENT");
      Fl_Button*  drawtd = new Fl_Button( 530, 30, 150, 30, "ALL DOCUMENTS"); 
      
   win->end();
   drawpnt->callback(  pntdoc );
   drawln->callback(  lndoc );
   drawpol->callback(  poldoc );
   drawtd->callback(  tddoc );
   win->show();}
   catch(...){
   Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Draw error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();}
 }
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main.cxx
void right(Fl_Widget* buttonptr){
     try{
     bound[0]=bound[0]-0.001;         
     bound[1]=bound[1];                                                              
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Right error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}

void left(Fl_Widget* buttonptr){
     try{
     bound[0]=bound[0]+0.001;    
     bound[1]=bound[1];                                                              
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Left error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}
	
void up(Fl_Widget* buttonptr){
     try{
     bound[0]=bound[0];
     bound[1]=bound[1]-0.001;                                                       
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Up error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}
	
void down(Fl_Widget* buttonptr){
     try{
     bound[0]=bound[0];
     bound[1]=bound[1]+0.001;                                                      
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Down error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}

void zoomIn(Fl_Widget* buttonptr){
     try{
     for (int i=0; i<coordx.size();i++)
    {
        coordx[i]=coordx[i]*2;
        coordx2[i]=coordx2[i]*2;
        coordy[i]=coordy[i]*2;
        coordy2[i]=coordy2[i]*2;
    } 
    bound[0]=bound[0]*2;
    bound[1]=bound[1]*2;
    if(paintpnt==true){
       for (int i=0; i<todox.size();i++)
       {
        todox[i]=todox[i]*2;
        todoy[i]=todoy[i]*2;
     }           
    }
    if(paintln==true){                                 //lineas
        for (int i=0; i<linx.size();i++)
        {
        linx[i]=linx[i]*2;
        linx2[i]=linx2[i]*2;
        liny[i]=liny[i]*2;
        liny2[i]=liny2[i]*2;
     }                
    }
    if(paintpol==true){                                //poligonos
       for (int i=0; i<geox.size();i++)
       {
        geox[i]=geox[i]*2;
        geox2[i]=geox2[i]*2;
        geoy[i]=geoy[i]*2;
        geoy2[i]=geoy2[i]*2;
     }           
    }
                                                      
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Zoom in error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}
void zoomOut(Fl_Widget* buttonptr){
   try{
     for (int i=0; i<coordx.size();i++)
    {
        coordx[i]=coordx[i]/2;
        coordx2[i]=coordx2[i]/2;
        coordy[i]=coordy[i]/2;
        coordy2[i]=coordy2[i]/2;                         
    }
    bound[0]=bound[0]/2;
    bound[1]=bound[1]/2;
    if(paintpnt==true){
       for (int i=0; i<todox.size();i++)
       {
        todox[i]=todox[i]/2;
        todoy[i]=todoy[i]/2;
     }           
    }
    if(paintln==true){                                 //lineas
        for (int i=0; i<linx.size();i++)
        {
        linx[i]=linx[i]/2;
        linx2[i]=linx2[i]/2;
        liny[i]=liny[i]/2;
        liny2[i]=liny2[i]/2;
     }                
    }
    if(paintpol==true){                                //poligonos
       for (int i=0; i<geox.size();i++)
       {
        geox[i]=geox[i]/2;
        geox2[i]=geox2[i]/2;
        geoy[i]=geoy[i]/2;
        geoy2[i]=geoy2[i]/2;
     }           
    }
     
    psimpl::simplify_douglas_peucker_n <4> (
    coordxz.begin (), coordxz.end (),
    tolerance, std::back_inserter (coordxsimp));
    psimpl::simplify_douglas_peucker_n <4> (
    coordxz2.begin (), coordxz2.end (),
    tolerance, std::back_inserter (coordx2simp));
    psimpl::simplify_douglas_peucker_n <4> (
    coordyz.begin (), coordyz.end (),
    tolerance, std::back_inserter (coordysimp));
    psimpl::simplify_douglas_peucker_n <4> (
    coordyz2.begin (), coordyz2.end (),
    tolerance, std::back_inserter (coordy2simp));
    
    string datossimp="";                    
    datossimp+="<?xml version='1.0' encoding='utf-8' ?>\n<kml xmlns='http://earth.google.com/kml/2.2'>\n<Document>\n<name>SanJose</name>\n<Placemark>\n<Style><LineStyle><color>ff0000ff</color></LineStyle><PolyStyle><fill>0</fill></PolyStyle></Style>\n<LineString>\n<coordinates>\n";
    for(int i=0;i<coordxsimp.size();i++){
        ostringstream sstream;
        sstream << coordxsimp[i];
        string coordx = sstream.str();
        ostringstream sstreama;
        sstreama << coordysimp[i];
        string coordy = sstreama.str();
        ostringstream sstreamz;
        sstreamz << coordx2simp[i];
        string coordx2 = sstreamz.str();
        ostringstream sstreamaz;
        sstreamaz << coordy2simp[i];
        string coordy2 = sstreamaz.str();
    datossimp+=coordx+","+coordy+"\n"+coordx2+","+coordy2+"\n";}
    datossimp+="</coordinates>\n</LineString>\n</Placemark>\n</Document>\n</kml>";
    char *datasimp=new char[datossimp.length() + 1];     
   	strcpy(datasimp, datossimp.c_str());
   	datosimp=datasimp;
   	creararch archivosimp;
    archivosimp.crearArchivo(filenamesimp,datosimp); 
       
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Zoom out error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}

void reset(Fl_Widget* buttonptr){
     try{
     bound=boundz;
     coordx=coordxz;
     coordx2=coordxz2;
     coordy=coordyz;
     coordy2=coordyz2; 
     todox=todoxz;
     todoy=todoyz;
     linx=linxz;
     linx2=linx2z;
     liny=linyz;
     liny2=liny2z;
     geox=geoxz;
     geox2=geox2z;
     geoy=geoyz;
     geoy2=geoy2z;
    }
     catch(...){Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Restore error");
	box->box(FL_UP_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
	}}

int main(int argc, char **argv) 
{
try{
// Create a window - width, height, label (=title)
Fl_Double_Window win(1000,700);
win.label("MAPAS");
// Set color of window to white
win.color(FL_WHITE);
// Begin adding children to this window
win.begin();
         //Create a button - x , y , width, height, label
       Fl_Button but(5,5,80,30,"OPEN");
       Fl_Button *buttonZoomIn = new Fl_Button(100,5,80,30,"ZOOM IN");
       Fl_Button *buttonReset = new Fl_Button(200,5,80,30,"RESET");
       Fl_Button *buttonZoomOut = new Fl_Button(300,5,80,30,"ZOOM OUT");
       Fl_Button *buttonUp = new Fl_Button(400,5,80,30,"UP");
       Fl_Button *buttonDown = new Fl_Button(500,5,80,30,"DOWN");
       Fl_Button *buttonLeft = new Fl_Button(600,5,80,30,"LEFT");
       Fl_Button *buttonRight = new Fl_Button(700,5,80,30,"RIGHT");
       Fl_Button *buttonDoc = new Fl_Button(800,5,80,30,"DRAW DOC");
       Fl_Button *buttonDocC = new Fl_Button(900,5,95,30,"CREATE DOC");
       //register callback function with this button
       buttonZoomIn->callback(zoomIn);
       buttonReset->callback(reset);
       buttonZoomOut->callback(zoomOut);
       buttonLeft->callback(left);
       buttonRight->callback(right);
       buttonUp->callback(up);
       buttonDown->callback(down);
       buttonDoc->callback(doc_window);
       buttonDocC->callback(createdoc);
       but.callback(open_window);  
       MyCanvas canvas(0,50,2000,2000);
       
// Stop adding children to this window
      
      win.end();
      win.resizable(win);
      // Display the window
      win.show();
      
      // Run and return
      return Fl::run();}
catch(...){
    Fl_Window *window;
	Fl_Box *box;
	window = new Fl_Window(300, 180);
	box = new Fl_Box(20, 40, 260, 100, "Critical error");
	box->box(FL_UP_BOX);
	box->labelsize(24);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show();
    return Fl::run();}
}
