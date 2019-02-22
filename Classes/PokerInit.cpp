//
//  PokerInit.cpp
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#include "PokerInit.h"
static PokerInit * sh;
PokerInit * PokerInit::sharedPokerInit()
{
    if (sh==NULL) {
        sh=new PokerInit();
    }
    return sh;
}

std::map<std::string, std::vector<Sprite *>> PokerInit::initArraysAndRootDic()
{
    
    //save four "2" in arrA
    Sprite* a1 = Sprite::create("F3.png");
    Sprite* a2 = Sprite::create("HT3.png");
    Sprite* a3 = Sprite::create("Meihua3.png");
    Sprite* a4 = Sprite::create("H3.png");
    arrA = std::vector<Sprite *>();
    arrA.push_back(a1);
    arrA.push_back(a2);
    arrA.push_back(a3);
    arrA.push_back(a4);
    
    //save four "3" in arrB
    Sprite* b1 = Sprite::create("F4.png");
    Sprite* b2 = Sprite::create("HT4.png");
    Sprite* b3 = Sprite::create("Meihua4.png");
    Sprite* b4 = Sprite::create("H4.png");
    arrB=std::vector<Sprite *>();
    arrB.push_back(b1);
    arrB.push_back(b2);
    arrB.push_back(b3);
    arrB.push_back(b4);
    
    //save four "4" in arrC
    Sprite* c1 = Sprite::create("F5.png");
    Sprite* c2 = Sprite::create("HT5.png");
    Sprite* c3 = Sprite::create("Meihua5.png");
    Sprite* c4 = Sprite::create("H5.png");
    arrC=std::vector<Sprite *>();
    arrC.push_back(c1);
    arrC.push_back(c2);
    arrC.push_back(c3);
    arrC.push_back(c4);
    
    //save four "5" in arrD
    Sprite* d1 = Sprite::create("F6.png");
    Sprite* d2 = Sprite::create("HT6.png");
    Sprite* d3 = Sprite::create("Meihua6.png");
    Sprite* d4 = Sprite::create("H6.png");
    arrD=std::vector<Sprite *>();
    arrD.push_back(d1);
    arrD.push_back(d2);
    arrD.push_back(d3);
    arrD.push_back(d4);
    
    //save four "6" in arrE
    Sprite* e1 = Sprite::create("F7.png");
    Sprite* e2 = Sprite::create("HT7.png");
    Sprite* e3 = Sprite::create("Meihua7.png");
    Sprite* e4 = Sprite::create("H7.png");
    arrE=std::vector<Sprite *>();
    arrE.push_back(e1);
    arrE.push_back(e2);
    arrE.push_back(e3);
    arrE.push_back(e4);
    
    //save four "7" in arrF
    Sprite* f1 = Sprite::create("F8.png");
    Sprite* f2 = Sprite::create("HT8.png");
    Sprite* f3 = Sprite::create("Meihua8.png");
    Sprite* f4 = Sprite::create("H8.png");
    arrF=std::vector<Sprite *>();
    arrF.push_back(f1);
    arrF.push_back(f2);
    arrF.push_back(f3);
    arrF.push_back(f4);
    
    //save four "8" in arrG
    Sprite* g1 = Sprite::create("F9.png");
    Sprite* g2 = Sprite::create("HT9.png");
    Sprite* g3 = Sprite::create("Meihua9.png");
    Sprite* g4 = Sprite::create("H9.png");
    arrG=std::vector<Sprite *>();
    arrG.push_back(g1);
    arrG.push_back(g2);
    arrG.push_back(g3);
    arrG.push_back(g4);
    
    //save four "9" in arrH
    Sprite* h1 = Sprite::create("F10.png");
    Sprite* h2 = Sprite::create("HT10.png");
    Sprite* h3 = Sprite::create("Meihua10.png");
    Sprite* h4 = Sprite::create("H10.png");
    arrH=std::vector<Sprite *>();
    arrH.push_back(h1);
    arrH.push_back(h2);
    arrH.push_back(h3);
    arrH.push_back(h4);
    
    //save four "10" in arrI
    Sprite* i1 = Sprite::create("F11.png");
    Sprite* i2 = Sprite::create("HT11.png");
    Sprite* i3 = Sprite::create("Meihua11.png");
    Sprite* i4 = Sprite::create("H11.png");
    arrI=std::vector<Sprite *>();
    arrI.push_back(i1);
    arrI.push_back(i2);
    arrI.push_back(i3);
    arrI.push_back(i4);
    
    //save four "11" in arrJ
    Sprite* j1 = Sprite::create("F12.png");
    Sprite* j2 = Sprite::create("HT12.png");
    Sprite* j3 = Sprite::create("Meihua12.png");
    Sprite* j4 = Sprite::create("H12.png");
    arrJ=std::vector<Sprite *>();
    arrJ.push_back(j1);
    arrJ.push_back(j2);
    arrJ.push_back(j3);
    arrJ.push_back(j4);
    
    //save four "12" in arrK
    Sprite* k1 = Sprite::create("F13.png");
    Sprite* k2 = Sprite::create("HT13.png");
    Sprite* k3 = Sprite::create("Meihua13.png");
    Sprite* k4 = Sprite::create("H13.png");
    arrK=std::vector<Sprite *>();
    arrK.push_back(k1);
    arrK.push_back(k2);
    arrK.push_back(k3);
    arrK.push_back(k4);
    
    //save four "13" in arrL
    Sprite* l1 = Sprite::create("F1.png");
    Sprite* l2 = Sprite::create("HT1.png");
    Sprite* l3 = Sprite::create("Meihua1.png");
    Sprite* l4 = Sprite::create("H1.png");
    arrL=std::vector<Sprite *>();
    arrL.push_back(l1);
    arrL.push_back(l2);
    arrL.push_back(l3);
    arrL.push_back(l4);
    
    //save four "1" in arrM
    Sprite* m1 = Sprite::create("F2.png");
    Sprite* m2 = Sprite::create("HT2.png");
    Sprite* m3 = Sprite::create("Meihua2.png");
    Sprite* m4 = Sprite::create("H2.png");
    arrM=std::vector<Sprite *>();
    arrM.push_back(m1);
    arrM.push_back(m2);
    arrM.push_back(m3);
    arrM.push_back(m4);
    
    //save four "xw" in arrN
    Sprite* n1 = Sprite::create("XW.png");
    arrN=std::vector<Sprite *>();
    arrN.push_back(n1);
    
    //save four "dw" in arrO
    Sprite* t1 = Sprite::create("DW.png");
    arrT=std::vector<Sprite *>();
    arrT.push_back(t1);
    
    rootDic = std::map<std::string, std::vector<Sprite *>>();
    rootDic["A"] = arrA;
    
  
    rootDic["B"] = arrB;
    rootDic["C"] = arrC;
    rootDic["D"] = arrD;
    rootDic["E"] = arrE;
    rootDic["F"] = arrF;
    rootDic["G"] = arrG;
    rootDic["H"] = arrH;
    
    rootDic["I"] = arrI;
    rootDic["J"] = arrJ;
    rootDic["K"] = arrK;
    rootDic["L"] = arrL;
    
    rootDic["M"] = arrM;
    rootDic["N"] = arrN;
    rootDic["T"] = arrT;
    return rootDic;

}
PokerInit::~PokerInit()
{
    arrA.clear();
    arrB.clear();
    arrC.clear();
    arrD.clear();
    arrE.clear();
    arrF.clear();
    arrG.clear();
    arrH.clear();
    arrI.clear();
    arrJ.clear();
    arrK.clear();
    arrL.clear();
    arrM.clear();
    arrN.clear();
    arrT.clear();
    rootDic.clear();
}

