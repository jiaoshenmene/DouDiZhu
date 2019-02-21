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
    CCSprite* a1 = CCSprite::create("F3.png");
    CCSprite* a2 = CCSprite::create("HT3.png");
    CCSprite* a3 = CCSprite::create("Meihua3.png");
    CCSprite* a4 = CCSprite::create("H3.png");
    arrA=new CCArray();
    arrA->addObject(a1);
    arrA->addObject(a2);
    arrA->addObject(a3);
    arrA->addObject(a4);
    
    //save four "3" in arrB
    CCSprite* b1 = CCSprite::create("F4.png");
    CCSprite* b2 = CCSprite::create("HT4.png");
    CCSprite* b3 = CCSprite::create("Meihua4.png");
    CCSprite* b4 = CCSprite::create("H4.png");
    arrB=new CCArray();
    arrB->addObject(b1);
    arrB->addObject(b2);
    arrB->addObject(b3);
    arrB->addObject(b4);
    
    //save four "4" in arrC
    CCSprite* c1 = CCSprite::create("F5.png");
    CCSprite* c2 = CCSprite::create("HT5.png");
    CCSprite* c3 = CCSprite::create("Meihua5.png");
    CCSprite* c4 = CCSprite::create("H5.png");
    arrC=new CCArray();
    arrC->addObject(c1);
    arrC->addObject(c2);
    arrC->addObject(c3);
    arrC->addObject(c4);
    
    //save four "5" in arrD
    CCSprite* d1 = CCSprite::create("F6.png");
    CCSprite* d2 = CCSprite::create("HT6.png");
    CCSprite* d3 = CCSprite::create("Meihua6.png");
    CCSprite* d4 = CCSprite::create("H6.png");
    arrD=new CCArray();
    arrD->addObject(d1);
    arrD->addObject(d2);
    arrD->addObject(d3);
    arrD->addObject(d4);
    
    //save four "6" in arrE
    CCSprite* e1 = CCSprite::create("F7.png");
    CCSprite* e2 = CCSprite::create("HT7.png");
    CCSprite* e3 = CCSprite::create("Meihua7.png");
    CCSprite* e4 = CCSprite::create("H7.png");
    arrE=new CCArray();
    arrE->addObject(e1);
    arrE->addObject(e2);
    arrE->addObject(e3);
    arrE->addObject(e4);
    
    //save four "7" in arrF
    CCSprite* f1 = CCSprite::create("F8.png");
    CCSprite* f2 = CCSprite::create("HT8.png");
    CCSprite* f3 = CCSprite::create("Meihua8.png");
    CCSprite* f4 = CCSprite::create("H8.png");
    arrF=new CCArray();
    arrF->addObject(f1);
    arrF->addObject(f2);
    arrF->addObject(f3);
    arrF->addObject(f4);
    
    //save four "8" in arrG
    CCSprite* g1 = CCSprite::create("F9.png");
    CCSprite* g2 = CCSprite::create("HT9.png");
    CCSprite* g3 = CCSprite::create("Meihua9.png");
    CCSprite* g4 = CCSprite::create("H9.png");
    arrG=new CCArray();
    arrG->addObject(g1);
    arrG->addObject(g2);
    arrG->addObject(g3);
    arrG->addObject(g4);
    
    //save four "9" in arrH
    CCSprite* h1 = CCSprite::create("F10.png");
    CCSprite* h2 = CCSprite::create("HT10.png");
    CCSprite* h3 = CCSprite::create("Meihua10.png");
    CCSprite* h4 = CCSprite::create("H10.png");
    arrH=new CCArray();
    arrH->addObject(h1);
    arrH->addObject(h2);
    arrH->addObject(h3);
    arrH->addObject(h4);
    
    //save four "10" in arrI
    CCSprite* i1 = CCSprite::create("F11.png");
    CCSprite* i2 = CCSprite::create("HT11.png");
    CCSprite* i3 = CCSprite::create("Meihua11.png");
    CCSprite* i4 = CCSprite::create("H11.png");
    arrI=new CCArray();
    arrI->addObject(i1);
    arrI->addObject(i2);
    arrI->addObject(i3);
    arrI->addObject(i4);
    
    //save four "11" in arrJ
    CCSprite* j1 = CCSprite::create("F12.png");
    CCSprite* j2 = CCSprite::create("HT12.png");
    CCSprite* j3 = CCSprite::create("Meihua12.png");
    CCSprite* j4 = CCSprite::create("H12.png");
    arrJ=new CCArray();
    arrJ->addObject(j1);
    arrJ->addObject(j2);
    arrJ->addObject(j3);
    arrJ->addObject(j4);
    
    //save four "12" in arrK
    CCSprite* k1 = CCSprite::create("F13.png");
    CCSprite* k2 = CCSprite::create("HT13.png");
    CCSprite* k3 = CCSprite::create("Meihua13.png");
    CCSprite* k4 = CCSprite::create("H13.png");
    arrK=new CCArray();
    arrK->addObject(k1);
    arrK->addObject(k2);
    arrK->addObject(k3);
    arrK->addObject(k4);
    
    //save four "13" in arrL
    CCSprite* l1 = CCSprite::create("F1.png");
    CCSprite* l2 = CCSprite::create("HT1.png");
    CCSprite* l3 = CCSprite::create("Meihua1.png");
    CCSprite* l4 = CCSprite::create("H1.png");
    arrL=new CCArray();
    arrL->addObject(l1);
    arrL->addObject(l2);
    arrL->addObject(l3);
    arrL->addObject(l4);
    
    //save four "1" in arrM
    CCSprite* m1 = CCSprite::create("F2.png");
    CCSprite* m2 = CCSprite::create("HT2.png");
    CCSprite* m3 = CCSprite::create("Meihua2.png");
    CCSprite* m4 = CCSprite::create("H2.png");
    arrM=new CCArray();
    arrM->addObject(m1);
    arrM->addObject(m2);
    arrM->addObject(m3);
    arrM->addObject(m4);
    
    //save four "xw" in arrN
    CCSprite* n1 = CCSprite::create("XW.png");
    arrN=new CCArray();
    arrN->addObject(n1);
    
    //save four "dw" in arrO
    CCSprite* t1 = CCSprite::create("DW.png");
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

