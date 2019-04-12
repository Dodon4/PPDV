#include "cell.h"
#include <iostream>
Cell::Cell()
{
    this->MaskPos = 0;
    this->SpirPos = 0;
    this->AsPos = 0;
    this->RodPos = 0;
    this->CalPat = 0;
    this->PSize = 0;
}
Cell::Cell(int &CalPat)
{
    this->MaskPos = 0;
    this->SpirPos = 0;
    this->AsPos = 0;
    this->RodPos = 0;
    this->CalPat = CalPat;
    this->PSize = 0;
}

Cell::Cell(int &MaskPos, int &SpirPos, int &AsPos, int &RodPos, int &CalPat, float &PSize)
{
    this->MaskPos = MaskPos;
    this->SpirPos = SpirPos;
    this->AsPos = AsPos;
    this->RodPos = RodPos;
    this->CalPat = CalPat;
    this->PSize = PSize;
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
int Cell::GetCalPat()
{
    return CalPat;
}
