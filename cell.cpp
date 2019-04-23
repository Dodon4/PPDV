#include "cell.h"
#include <iostream>
Cell::Cell():MaskPos(0),SpirPos(0),AsPos(0),RodPos(0),CalPat(0),PSize(0)
{
}
Cell::Cell(int &CalPat):MaskPos(0),SpirPos(0),AsPos(0),RodPos(0),CalPat(CalPat),PSize(0)
{
}

Cell::Cell(int MaskPos, int SpirPos, int AsPos, int RodPos, int CalPat, float PSize):
    MaskPos(MaskPos),SpirPos(SpirPos),AsPos(AsPos),RodPos(RodPos),CalPat(CalPat),PSize(PSize)
{
}

void Cell::SetPar(int MaskPos, int SpirPos, int AsPos, int RodPos, int CalPat, float PSize)
{
    this->MaskPos = MaskPos;
    this->SpirPos = SpirPos;
    this->AsPos = AsPos;
    this->RodPos = RodPos;
    this->CalPat = CalPat;
    this->PSize = PSize;
}

void Cell::GetPar()
{
    std::cout<<MaskPos<<"\t"<<SpirPos<<"\t"<<AsPos<<"\t"<<RodPos<<"\t"<<CalPat<<"\t"<<PSize<<"\n";
}
int Cell::GetAsPos()
{
    return AsPos;
}
