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

//Map<std::string, Vector<Sprite *> > PokerInit::initArraysAndRootDic()
//{
//    
//    //save four "2" in arrA
//    Sprite* a1 = Sprite::create("F3.png");
//    Sprite* a2 = Sprite::create("HT3.png");
//    Sprite* a3 = Sprite::create("Meihua3.png");
//    Sprite* a4 = Sprite::create("H3.png");
//    arrA = Vector<Sprite *>();
//    arrA.pushBack(a1);
//    arrA.pushBack(a2);
//    arrA.pushBack(a3);
//    arrA.pushBack(a4);
//    
//    //save four "3" in arrB
//    Sprite* b1 = Sprite::create("F4.png");
//    Sprite* b2 = Sprite::create("HT4.png");
//    Sprite* b3 = Sprite::create("Meihua4.png");
//    Sprite* b4 = Sprite::create("H4.png");
//    arrB=Vector<Sprite *>();
//    arrB.pushBack(b1);
//    arrB.pushBack(b2);
//    arrB.pushBack(b3);
//    arrB.pushBack(b4);
//    
//    //save four "4" in arrC
//    Sprite* c1 = Sprite::create("F5.png");
//    Sprite* c2 = Sprite::create("HT5.png");
//    Sprite* c3 = Sprite::create("Meihua5.png");
//    Sprite* c4 = Sprite::create("H5.png");
//    arrC=Vector<Sprite *>();
//    arrC.pushBack(c1);
//    arrC.pushBack(c2);
//    arrC.pushBack(c3);
//    arrC.pushBack(c4);
//    
//    //save four "5" in arrD
//    Sprite* d1 = Sprite::create("F6.png");
//    Sprite* d2 = Sprite::create("HT6.png");
//    Sprite* d3 = Sprite::create("Meihua6.png");
//    Sprite* d4 = Sprite::create("H6.png");
//    arrD=Vector<Sprite *>();
//    arrD.pushBack(d1);
//    arrD.pushBack(d2);
//    arrD.pushBack(d3);
//    arrD.pushBack(d4);
//    
//    //save four "6" in arrE
//    Sprite* e1 = Sprite::create("F7.png");
//    Sprite* e2 = Sprite::create("HT7.png");
//    Sprite* e3 = Sprite::create("Meihua7.png");
//    Sprite* e4 = Sprite::create("H7.png");
//    arrE=Vector<Sprite *>();
//    arrE.pushBack(e1);
//    arrE.pushBack(e2);
//    arrE.pushBack(e3);
//    arrE.pushBack(e4);
//    
//    //save four "7" in arrF
//    Sprite* f1 = Sprite::create("F8.png");
//    Sprite* f2 = Sprite::create("HT8.png");
//    Sprite* f3 = Sprite::create("Meihua8.png");
//    Sprite* f4 = Sprite::create("H8.png");
//    arrF=Vector<Sprite *>();
//    arrF.pushBack(f1);
//    arrF.pushBack(f2);
//    arrF.pushBack(f3);
//    arrF.pushBack(f4);
//    
//    //save four "8" in arrG
//    Sprite* g1 = Sprite::create("F9.png");
//    Sprite* g2 = Sprite::create("HT9.png");
//    Sprite* g3 = Sprite::create("Meihua9.png");
//    Sprite* g4 = Sprite::create("H9.png");
//    arrG=Vector<Sprite *>();
//    arrG.pushBack(g1);
//    arrG.pushBack(g2);
//    arrG.pushBack(g3);
//    arrG.pushBack(g4);
//    
//    //save four "9" in arrH
//    Sprite* h1 = Sprite::create("F10.png");
//    Sprite* h2 = Sprite::create("HT10.png");
//    Sprite* h3 = Sprite::create("Meihua10.png");
//    Sprite* h4 = Sprite::create("H10.png");
//    arrH=Vector<Sprite *>();
//    arrH.pushBack(h1);
//    arrH.pushBack(h2);
//    arrH.pushBack(h3);
//    arrH.pushBack(h4);
//    
//    //save four "10" in arrI
//    Sprite* i1 = Sprite::create("F11.png");
//    Sprite* i2 = Sprite::create("HT11.png");
//    Sprite* i3 = Sprite::create("Meihua11.png");
//    Sprite* i4 = Sprite::create("H11.png");
//    arrI=Vector<Sprite *>();
//    arrI.pushBack(i1);
//    arrI.pushBack(i2);
//    arrI.pushBack(i3);
//    arrI.pushBack(i4);
//    
//    //save four "11" in arrJ
//    Sprite* j1 = Sprite::create("F12.png");
//    Sprite* j2 = Sprite::create("HT12.png");
//    Sprite* j3 = Sprite::create("Meihua12.png");
//    Sprite* j4 = Sprite::create("H12.png");
//    arrJ=Vector<Sprite *>();
//    arrJ.pushBack(j1);
//    arrJ.pushBack(j2);
//    arrJ.pushBack(j3);
//    arrJ.pushBack(j4);
//    
//    //save four "12" in arrK
//    Sprite* k1 = Sprite::create("F13.png");
//    Sprite* k2 = Sprite::create("HT13.png");
//    Sprite* k3 = Sprite::create("Meihua13.png");
//    Sprite* k4 = Sprite::create("H13.png");
//    arrK=Vector<Sprite *>();
//    arrK.pushBack(k1);
//    arrK.pushBack(k2);
//    arrK.pushBack(k3);
//    arrK.pushBack(k4);
//    
//    //save four "13" in arrL
//    Sprite* l1 = Sprite::create("F1.png");
//    Sprite* l2 = Sprite::create("HT1.png");
//    Sprite* l3 = Sprite::create("Meihua1.png");
//    Sprite* l4 = Sprite::create("H1.png");
//    arrL=Vector<Sprite *>();
//    arrL.pushBack(l1);
//    arrL.pushBack(l2);
//    arrL.pushBack(l3);
//    arrL.pushBack(l4);
//    
//    //save four "1" in arrM
//    Sprite* m1 = Sprite::create("F2.png");
//    Sprite* m2 = Sprite::create("HT2.png");
//    Sprite* m3 = Sprite::create("Meihua2.png");
//    Sprite* m4 = Sprite::create("H2.png");
//    arrM=Vector<Sprite *>();
//    arrM.pushBack(m1);
//    arrM.pushBack(m2);
//    arrM.pushBack(m3);
//    arrM.pushBack(m4);
//    
//    //save four "xw" in arrN
//    Sprite* n1 = Sprite::create("XW.png");
//    arrN=Vector<Sprite *>();
//    arrN.pushBack(n1);
//    
//    //save four "dw" in arrO
//    Sprite* t1 = Sprite::create("DW.png");
//    arrT=Vector<Sprite *>();
//    arrT.pushBack(t1);
//    
//    rootDic = Map<std::string, Vector<Sprite *> >();
//    rootDic.insert("A", arrA);
//    rootDic.insert("B", arrB);
//    rootDic.insert("C", arrC);
//    rootDic.insert("D", arrD);
//    rootDic.insert("E", arrE);
//    rootDic.insert("F", arrF);
//    rootDic.insert("G", arrG);
//    rootDic.insert("H", arrH);
//    
//    rootDic.insert("I", arrI);
//    rootDic.insert("J", arrJ);
//    rootDic.insert("K", arrK);
//    rootDic.insert("L", arrL);
//    
//    rootDic.insert("M", arrM);
//    rootDic.insert("N", arrN);
//    rootDic.insert("T", arrT);
//    
//    return rootDic;
//
//}
PokerInit::~PokerInit()
{
//    arrA.clear();
//    arrB.clear();
//    arrC.clear();
//    arrD.clear();
//    arrE.clear();
//    arrF.clear();
//    arrG.clear();
//    arrH.clear();
//    arrI.clear();
//    arrJ.clear();
//    arrK.clear();
//    arrL.clear();
//    arrM.clear();
//    arrN.clear();
//    arrT.clear();
//    rootDic.clear();
}

