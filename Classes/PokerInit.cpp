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

CCDictionary * PokerInit::initArraysAndRootDic()
{
    //save four "2" in arrA
    Sprite* a1 = Sprite::create("F3.png");
    Sprite* a2 = Sprite::create("HT3.png");
    Sprite* a3 = Sprite::create("Meihua3.png");
    Sprite* a4 = Sprite::create("H3.png");
    arrA=new CCArray();
    arrA->addObject(a1);
    arrA->addObject(a2);
    arrA->addObject(a3);
    arrA->addObject(a4);
    
    //save four "3" in arrB
    Sprite* b1 = Sprite::create("F4.png");
    Sprite* b2 = Sprite::create("HT4.png");
    Sprite* b3 = Sprite::create("Meihua4.png");
    Sprite* b4 = Sprite::create("H4.png");
    arrB=new CCArray();
    arrB->addObject(b1);
    arrB->addObject(b2);
    arrB->addObject(b3);
    arrB->addObject(b4);
    
    //save four "4" in arrC
    Sprite* c1 = Sprite::create("F5.png");
    Sprite* c2 = Sprite::create("HT5.png");
    Sprite* c3 = Sprite::create("Meihua5.png");
    Sprite* c4 = Sprite::create("H5.png");
    arrC=new CCArray();
    arrC->addObject(c1);
    arrC->addObject(c2);
    arrC->addObject(c3);
    arrC->addObject(c4);
    
    //save four "5" in arrD
    Sprite* d1 = Sprite::create("F6.png");
    Sprite* d2 = Sprite::create("HT6.png");
    Sprite* d3 = Sprite::create("Meihua6.png");
    Sprite* d4 = Sprite::create("H6.png");
    arrD=new CCArray();
    arrD->addObject(d1);
    arrD->addObject(d2);
    arrD->addObject(d3);
    arrD->addObject(d4);
    
    //save four "6" in arrE
    Sprite* e1 = Sprite::create("F7.png");
    Sprite* e2 = Sprite::create("HT7.png");
    Sprite* e3 = Sprite::create("Meihua7.png");
    Sprite* e4 = Sprite::create("H7.png");
    arrE=new CCArray();
    arrE->addObject(e1);
    arrE->addObject(e2);
    arrE->addObject(e3);
    arrE->addObject(e4);
    
    //save four "7" in arrF
    Sprite* f1 = Sprite::create("F8.png");
    Sprite* f2 = Sprite::create("HT8.png");
    Sprite* f3 = Sprite::create("Meihua8.png");
    Sprite* f4 = Sprite::create("H8.png");
    arrF=new CCArray();
    arrF->addObject(f1);
    arrF->addObject(f2);
    arrF->addObject(f3);
    arrF->addObject(f4);
    
    //save four "8" in arrG
    Sprite* g1 = Sprite::create("F9.png");
    Sprite* g2 = Sprite::create("HT9.png");
    Sprite* g3 = Sprite::create("Meihua9.png");
    Sprite* g4 = Sprite::create("H9.png");
    arrG=new CCArray();
    arrG->addObject(g1);
    arrG->addObject(g2);
    arrG->addObject(g3);
    arrG->addObject(g4);
    
    //save four "9" in arrH
    Sprite* h1 = Sprite::create("F10.png");
    Sprite* h2 = Sprite::create("HT10.png");
    Sprite* h3 = Sprite::create("Meihua10.png");
    Sprite* h4 = Sprite::create("H10.png");
    arrH=new CCArray();
    arrH->addObject(h1);
    arrH->addObject(h2);
    arrH->addObject(h3);
    arrH->addObject(h4);
    
    //save four "10" in arrI
    Sprite* i1 = Sprite::create("F11.png");
    Sprite* i2 = Sprite::create("HT11.png");
    Sprite* i3 = Sprite::create("Meihua11.png");
    Sprite* i4 = Sprite::create("H11.png");
    arrI=new CCArray();
    arrI->addObject(i1);
    arrI->addObject(i2);
    arrI->addObject(i3);
    arrI->addObject(i4);
    
    //save four "11" in arrJ
    Sprite* j1 = Sprite::create("F12.png");
    Sprite* j2 = Sprite::create("HT12.png");
    Sprite* j3 = Sprite::create("Meihua12.png");
    Sprite* j4 = Sprite::create("H12.png");
    arrJ=new CCArray();
    arrJ->addObject(j1);
    arrJ->addObject(j2);
    arrJ->addObject(j3);
    arrJ->addObject(j4);
    
    //save four "12" in arrK
    Sprite* k1 = Sprite::create("F13.png");
    Sprite* k2 = Sprite::create("HT13.png");
    Sprite* k3 = Sprite::create("Meihua13.png");
    Sprite* k4 = Sprite::create("H13.png");
    arrK=new CCArray();
    arrK->addObject(k1);
    arrK->addObject(k2);
    arrK->addObject(k3);
    arrK->addObject(k4);
    
    //save four "13" in arrL
    Sprite* l1 = Sprite::create("F1.png");
    Sprite* l2 = Sprite::create("HT1.png");
    Sprite* l3 = Sprite::create("Meihua1.png");
    Sprite* l4 = Sprite::create("H1.png");
    arrL=new CCArray();
    arrL->addObject(l1);
    arrL->addObject(l2);
    arrL->addObject(l3);
    arrL->addObject(l4);
    
    //save four "1" in arrM
    Sprite* m1 = Sprite::create("F2.png");
    Sprite* m2 = Sprite::create("HT2.png");
    Sprite* m3 = Sprite::create("Meihua2.png");
    Sprite* m4 = Sprite::create("H2.png");
    arrM=new CCArray();
    arrM->addObject(m1);
    arrM->addObject(m2);
    arrM->addObject(m3);
    arrM->addObject(m4);
    
    //save four "xw" in arrN
    Sprite* n1 = Sprite::create("XW.png");
    arrN=new CCArray();
    arrN->addObject(n1);
    
    //save four "dw" in arrO
    Sprite* t1 = Sprite::create("DW.png");
    arrT=new CCArray();
    arrT->addObject(t1);
    
    rootDic=new CCDictionary();
    rootDic->setObject(arrA, "A");
    rootDic->setObject(arrB, "B");
    rootDic->setObject(arrC, "C");
    rootDic->setObject(arrD, "D");
    rootDic->setObject(arrE, "E");
    rootDic->setObject(arrF, "F");
    rootDic->setObject(arrG, "G");
    rootDic->setObject(arrH, "H");
    rootDic->setObject(arrI, "I");
    rootDic->setObject(arrJ, "J");
    rootDic->setObject(arrK, "K");
    rootDic->setObject(arrL, "L");
    rootDic->setObject(arrM, "M");
    rootDic->setObject(arrN, "N");
    rootDic->setObject(arrT, "T");
    
    return rootDic;

}
PokerInit::~PokerInit()
{
    arrA->release();
    arrB->release();
    arrC->release();
    arrD->release();
    arrE->release();
    arrF->release();
    arrG->release();
    arrH->release();
    arrI->release();
    arrJ->release();
    arrK->release();
    arrL->release();
    arrM->release();
    arrN->release();
    arrT->release();
    rootDic->release();
}

