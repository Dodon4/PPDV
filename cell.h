#ifndef CELL_H
#define CELL_H


class Cell
{
private:
    int MaskPos, SpirPos,AsPos, RodPos, CalPat;
    float PSize;
public:
    Cell();
    Cell(int &CalPat);
    Cell(int &MaskPos, int &SpirPos, int &AsPos, int &RodPos, int &CalPat, float &PSize);
    void SetPar(int MaskPos, int SpirPos,int AsPos,int RodPos,int CalPat,float PSize);
    void GetPar();
    int GetCalPat();
};

#endif // CELL_H
