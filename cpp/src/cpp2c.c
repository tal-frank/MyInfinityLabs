/**********************
* cpp2c
* Author: Tal Frank
* Reviewer: Yael Novick
* Last update: 09/09/2026
**********************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#define UNUSED(x) (void)(x)

static int s_count = 0; 

/*--------------------------------------------------------------------------------*/
/*################################# TYPEDEFS #####################################*/
/*--------------------------------------------------------------------------------*/

typedef struct Vtable Vtable;
typedef struct PublicTransport PublicTransport;
typedef struct Minibus Minibus;
typedef struct ArmyMinibus ArmyMinibus;
typedef struct Taxi Taxi;
typedef struct SpecialTaxi SpecialTaxi;
typedef struct PublicConvoy PublicConvoy;

/*----------------------------------------------------------------------------------------------*/
/*################################# FUNCTIONS DECLARATIONS #####################################*/
/*----------------------------------------------------------------------------------------------*/

/*---------- PublicTransport member functions ----------*/

void PublicTransportCtor(PublicTransport* const this);
void PublicTransportCCtor(PublicTransport* const this,
                          PublicTransport* const other_);
void PublicTransportDtor(PublicTransport* const this);
void PublicTransportdisplay(PublicTransport* const this);
void PublicTransportprint_count(void);
int PublicTransportGet_ID(PublicTransport* const this);

/*---------- Minibus member functions ----------*/

void MinibusCtor(Minibus* const this);
void MinibusCCtor(Minibus* const this,
                  Minibus* const other_);
void MinibusAssign(Minibus* const this,
                   Minibus* const other_);
void MinibusDtor(Minibus* const this);
void Minibusdisplay(Minibus* const this);
void MinibusWash(Minibus* const this, int minutes);

/*---------- ArmyMinibus member functions ----------*/

void ArmyMinibusCtor(ArmyMinibus* const this);
void ArmyMinibusCCtor(ArmyMinibus* const this,
                      ArmyMinibus* const other_);
void ArmyMinibusAssign(ArmyMinibus* const this,
                       ArmyMinibus* const other_);
void ArmyMinibusDtor(ArmyMinibus* const this);

/*---------- Taxi member functions ----------*/

void TaxiCtor(Taxi* const this);
void TaxiCCtor(Taxi* const this,
               Taxi* const other_);
void TaxiAssign(Taxi* const this,
                Taxi* const other_);
void TaxiDtor(Taxi* const this);
void Taxidisplay(Taxi* const this);

/*---------- SpecialTaxi member functions ----------*/

void SpecialTaxiCtor(SpecialTaxi* const this);
void SpecialTaxiCCtor(SpecialTaxi* const this,
                      SpecialTaxi* const other_);
void SpecialTaxiAssign(SpecialTaxi* const this,
                       SpecialTaxi* const other_);
void SpecialTaxiDtor(SpecialTaxi* const this);
void SpecialTaxidisplay(SpecialTaxi* const this);

/*---------- PublicConvoy member functions ----------*/

void PublicConvoyCtor(PublicConvoy* const this);
void PublicConvoyCCtor(PublicConvoy* const this, PublicConvoy* const other_);
void PublicConvoyDtor(PublicConvoy* const this);
void PublicConvoydisplay(PublicConvoy* const this);

/*---------- rest of functions ----------*/

void print_info();
void print_infoPublicTransport(PublicTransport* a);
void Print_infoMinibus(Minibus* m);
void Taxi_displayTaxi(Taxi s);
PublicTransport Print_infoi(int i);

/*---------------------------------------------------------------------------------------*/
/*################################# STRUCTS #####################################*/
/*---------------------------------------------------------------------------------------*/

struct Vtable
{
    void (*Dtor)(void* const this);
    void (*display)(void* const this);
    void (*Wash)(void* const this, int minutes);
};

struct PublicTransport
{
    Vtable vptr;
    int m_license_plate;
};

struct Minibus
{
    PublicTransport PubTrans;
    int m_numSeats;
};

struct ArmyMinibus
{
    Minibus minibus;
};

struct Taxi
{
    PublicTransport PubTrans;
};

struct SpecialTaxi
{
    Taxi taxi;
};

struct PublicConvoy
{
    PublicTransport m_public_transport;
    PublicTransport* m_pt1;
    PublicTransport* m_pt2;
    Minibus m_m;
    Taxi m_t;
};

/*--------------------------------------------------------------------------------------*/
/*################################# VIRTAUL TABLES #####################################*/
/*--------------------------------------------------------------------------------------*/

Vtable PublicTransportVtable = {(void(*)(void*))PublicTransportDtor,
                                (void(*)(void*))PublicTransportdisplay,
                                NULL};

Vtable MinibusVtable = {(void(*)(void*))MinibusDtor,
                        (void(*)(void*))Minibusdisplay,
                        (void(*)(void*, int))MinibusWash};

Vtable ArmyMinibusVtable = {(void(*)(void*))ArmyMinibusDtor,
                            (void(*)(void*))Minibusdisplay,
                            (void(*)(void*, int))MinibusWash};

Vtable TaxiVtable = {(void(*)(void*))TaxiDtor,
                     (void(*)(void*))Taxidisplay,
                     NULL};

Vtable SpecialTaxiVtable = {(void(*)(void*))SpecialTaxiDtor,
                            (void(*)(void*))SpecialTaxidisplay,
                            NULL};

Vtable PublicConvoyVtable = {(void(*)(void*))PublicConvoyDtor,
                             (void(*)(void*))PublicConvoydisplay,
                             NULL};

/*-----------------------------------------------------------------------------*/
/*################################# CTORS #####################################*/
/*-----------------------------------------------------------------------------*/

void PublicTransportCtor(PublicTransport* const this)
{
    this->m_license_plate = ++s_count;    
    this->vptr = PublicTransportVtable;
    
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void MinibusCtor(Minibus* const this)
{
    PublicTransportCtor((PublicTransport*)this);
    this->m_numSeats = 20;    
    this->PubTrans.vptr = MinibusVtable;
    
    printf("Minibus::Ctor()\n");
}

void ArmyMinibusCtor(ArmyMinibus* const this)
{
    MinibusCtor((Minibus*)this);   
    this->minibus.PubTrans.vptr = ArmyMinibusVtable;
    
    printf("ArmyMinibus::Ctor()\n");
}

void TaxiCtor(Taxi* const this)
{
    PublicTransportCtor((PublicTransport*)this);
    this->PubTrans.vptr = TaxiVtable;

    printf("Taxi::Ctor()\n");
}

void SpecialTaxiCtor(SpecialTaxi* const this)
{
    TaxiCtor((Taxi*)this);
    this->taxi.PubTrans.vptr = SpecialTaxiVtable;

    printf("SpecialTaxi::Ctor()\n");
}

void PublicConvoyCtor(PublicConvoy* const this)
{
    PublicTransportCtor((PublicTransport*)this);
    this->m_public_transport.vptr = PublicConvoyVtable;

    this->m_pt1 = malloc(sizeof(Minibus));
    MinibusCtor((Minibus*)this->m_pt1);
    
    this->m_pt2 = malloc(sizeof(Taxi));
    TaxiCtor((Taxi*)this->m_pt2);

    MinibusCtor(&this->m_m);
    TaxiCtor(&this->m_t);

    printf("PublicConvo::Ctor()\n");
}

/*----------------------------------------------------------------------------------*/
/*################################# COPY CTORS #####################################*/
/*----------------------------------------------------------------------------------*/

void PublicTransportCCtor(PublicTransport* const this,
                          PublicTransport* const other_)
{
    UNUSED(other_);

    this->m_license_plate = ++s_count;    
    this->vptr = PublicTransportVtable;
    
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void MinibusCCtor(Minibus* const this,
                  Minibus* const other_)
{
    PublicTransportCCtor((PublicTransport*)this, (PublicTransport*)other_);
    this->m_numSeats = other_->m_numSeats;    
    this->PubTrans.vptr = MinibusVtable;
    
    printf("Minibus::CCtor()\n");
}

void ArmyMinibusCCtor(ArmyMinibus* const this,
                      ArmyMinibus* const other_)
{
    MinibusCCtor((Minibus*)this, (Minibus*)other_);   
    this->minibus.PubTrans.vptr = ArmyMinibusVtable;   
    
    printf("ArmyMinibus::CCtor()\n");
}

void TaxiCCtor(Taxi* const this,
               Taxi* const other_)
{
    PublicTransportCCtor((PublicTransport*)this, (PublicTransport*)other_);
    this->PubTrans.vptr = TaxiVtable;

    printf("Taxi::CCtor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi* const this,
                      SpecialTaxi* const other_)
{
    TaxiCCtor((Taxi*)this, (Taxi*)other_);
    this->taxi.PubTrans.vptr = SpecialTaxiVtable;

    printf("SpecialTaxi::CCtor()\n");
}

void PublicConvoyCCtor(PublicConvoy* const this,
                       PublicConvoy* const other_)
{
    PublicTransportCtor((PublicTransport*)this);
    this->m_public_transport.vptr = other_->m_public_transport.vptr;

    this->m_pt1 = malloc(sizeof(PublicTransport));
    PublicTransportCCtor(this->m_pt1, other_->m_pt1);
    /* this->m_pt1->vptr = other_->m_pt1->vptr; */

    this->m_pt2 = malloc(sizeof(PublicTransport));
    PublicTransportCCtor(this->m_pt2, other_->m_pt2);
    /* this->m_pt1->vptr = other_->m_pt1->vptr; */

    MinibusCCtor(&this->m_m, &other_->m_m);
    TaxiCCtor(&this->m_t, &other_->m_t);

    printf("PublicConvoy::CCtor\n");
}

/*-----------------------------------------------------------------------------*/
/*################################# DTORS #####################################*/
/*-----------------------------------------------------------------------------*/

void PublicTransportDtor(PublicTransport* const this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void MinibusDtor(Minibus* const this)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDtor((PublicTransport*)this);
}

void ArmyMinibusDtor(ArmyMinibus* const this)
{
    printf("ArmyMinibus::Dtor()\n");
    MinibusDtor((Minibus*)this);
}

void TaxiDtor(Taxi* const this)
{
    printf("Taxi::Dtor()\n");
    PublicTransportDtor((PublicTransport*)this);
}

void SpecialTaxiDtor(SpecialTaxi* const this)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor((Taxi*)this);
}

void PublicConvoyDtor(PublicConvoy* const this)
{
    printf("PublicConvoy::Dtor\n");
    this->m_pt1->vptr.Dtor(this->m_pt1);
    free(this->m_pt1);
    this->m_pt2->vptr.Dtor(this->m_pt2);
    free(this->m_pt2);

    TaxiDtor(&this->m_t);
    MinibusDtor(&this->m_m);
    PublicTransportDtor(&this->m_public_transport);
}

/*-----------------------------------------------------------------------------------------*/
/*################################# REST OF FUNCTIONS #####################################*/
/*-----------------------------------------------------------------------------------------*/

int PublicTransportGet_ID(PublicTransport* const this)
{
    return this->m_license_plate;
}

void PublicTransportprint_count()
{
    printf("s_count: %d\n", s_count);
}

/*------------------------------ display functions ------------------------------*/
/*-------------------------------------------------------------------------------*/

void PublicTransportdisplay(PublicTransport* const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void Minibusdisplay(Minibus* const this)
{
    printf("Minibus::display() ID: %d num seats: %d\n", 
            PublicTransportGet_ID(((PublicTransport*)this)), this->m_numSeats);
}

void Taxidisplay(Taxi* const this)
{
    printf("Taxi::display() ID: %d\n", 
            PublicTransportGet_ID(((PublicTransport*)this)));
}

void SpecialTaxidisplay(SpecialTaxi* const this)
{
    printf("SpecialTaxi::display() ID: %d\n", 
            PublicTransportGet_ID(((PublicTransport*)this)));
}

void PublicConvoydisplay(PublicConvoy* const this)
{
    this->m_pt1->vptr.display(this->m_pt1);
    this->m_pt2->vptr.display(this->m_pt2);
    Minibusdisplay(&this->m_m);
    Taxidisplay(&this->m_t);
}

/*------------------------------ wash functions ------------------------------*/
/*-----------------------------------------------------------------------------*/

void MinibusWash(Minibus* const this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", 
           minutes, PublicTransportGet_ID(((PublicTransport*)this)));
}

/*------------------------------ print info functions ------------------------------*/
/*----------------------------------------------------------------------------------*/

void print_info()
{
    PublicTransportprint_count();
}

void Print_infoMinibus(Minibus* m)
{
    MinibusWash(m, 3);
}

void print_infoPublicTransport(PublicTransport* a)
{
    PublicTransportdisplay(a);
}

PublicTransport Print_infoi(int i)
{
    Minibus minibus = {0};
    PublicTransport pub_trans_temp;
    MinibusCtor(&minibus);
    UNUSED(i);
    
    printf("print_info(int i)\n");
    Minibusdisplay(&minibus);
    PublicTransportCCtor(&pub_trans_temp, (PublicTransport*)&minibus);
    MinibusDtor(&minibus);
    return pub_trans_temp;
}

void Taxi_displayTaxi(Taxi s)
{
    Taxidisplay(&s);
}

int max_funci(const int* t1, const int* t2)
{
    return ((*t1 > *t2) ? *t1 : *t2);
}

/*----------------------------------------------------------------------------*/
/*################################# MAIN #####################################*/
/*----------------------------------------------------------------------------*/

int main(int arg, char** argv, char** envp)
{
/*---------------- initializations ----------------*/

    int i = 0;

    int num1;
    int num2;

    Minibus m;
    Minibus m2;
    Minibus minibus_temp;

    PublicTransport pub_trans_temp;

    Taxi taxi_temp;   

    SpecialTaxi special_taxi;

    PublicTransport* array[3];
    PublicTransport array2[3];
    Minibus array3[4];
    Taxi* array4 = NULL;

    ArmyMinibus* army_minibus_ptr;

    PublicConvoy* public_convoy_1;
    PublicConvoy* public_convoy_2;

    UNUSED(arg);
    UNUSED(argv);
    UNUSED(envp);

/*---------------- print infos ----------------*/

    MinibusCtor(&m);
    Print_infoMinibus(&m);
    pub_trans_temp = Print_infoi(3);

    PublicTransportdisplay(&pub_trans_temp);
    PublicTransportDtor(&pub_trans_temp);

/*---------------- array of references ----------------*/

    array[0] = malloc(sizeof(Minibus));
    MinibusCtor((Minibus*)array[0]);
    array[1] = malloc(sizeof(Taxi));
    TaxiCtor((Taxi*)array[1]);
    array[2] = malloc(sizeof(Minibus));
    MinibusCtor((Minibus*)array[2]);

    for (i = 0; i < 3; ++i)
    {
        array[i]->vptr.display(array[i]);
    }

    for(i = 0; i < 3; ++i)
    {
        array[i]->vptr.Dtor(array[i]);
        free(array[i]);
    }

/*---------------- array by value ----------------*/

    MinibusCtor(&minibus_temp);
    PublicTransportCCtor(&array2[0], (PublicTransport*)&minibus_temp);
    TaxiCtor(&taxi_temp);
    PublicTransportCCtor(&array2[1], (PublicTransport*)&taxi_temp);
    PublicTransportCtor(&array2[2]);
    
    TaxiDtor(&taxi_temp);
    MinibusDtor(&minibus_temp);

    for(i = 0; i < 3; ++i)
    {
        PublicTransportdisplay(&array2[i]);
    }

     print_infoPublicTransport(&array2[0]);

/*---------------- print count ----------------*/

    PublicTransportprint_count();
    MinibusCtor(&m2);
    PublicTransportprint_count();

/*---------------- array3 + array4 ----------------*/

    for(i = 0; i < 4; ++i)
    {
        MinibusCtor(&array3[i]);
    }
    /* MinibusCtor(&array3[0]);
    MinibusCtor(&array3[1]);
    MinibusCtor(&array3[2]);
    MinibusCtor(&array3[3]); */

    array4 = malloc(4 * sizeof(Taxi));
    for(i = 0; i < 4; ++i)
    {
        TaxiCtor(&array4[i]);
    }
    /* TaxiCtor(&array4[0]);
    TaxiCtor(&array4[1]);
    TaxiCtor(&array4[2]);
    TaxiCtor(&array4[3]); */

    for(i = 4; i > 0; --i)
    {
        TaxiDtor(&array4[i - 1]);
    }
    /* TaxiDtor(&array4[3]);
    TaxiDtor(&array4[2]);
    TaxiDtor(&array4[1]);
    TaxiDtor(&array4[0]); */

/*---------------- template ----------------*/

    num1 = 1;
    num2 = 2;
    printf("%d\n", max_funci(&num1, &num2));
    num2 = 2.0f;
    printf("%d\n", max_funci(&num1, (int*)&num2));

/*---------------- special taxi display ----------------*/

    SpecialTaxiCtor(&special_taxi);
    TaxiCCtor(&taxi_temp, (Taxi*)&special_taxi);
    Taxi_displayTaxi(taxi_temp);
    TaxiDtor(&taxi_temp);

/*---------------- PublicConvoy ----------------*/

    public_convoy_1 = malloc(sizeof(PublicConvoy));
    PublicConvoyCtor(public_convoy_1);
    public_convoy_2 = malloc(sizeof(PublicConvoy));
    PublicConvoyCCtor(public_convoy_2, public_convoy_1);

    public_convoy_1->m_public_transport.vptr.display(public_convoy_1);
    public_convoy_2->m_public_transport.vptr.display(public_convoy_2);

    PublicConvoyDtor(public_convoy_1);
    free(public_convoy_1);

    public_convoy_2->m_public_transport.vptr.display(public_convoy_2);

    PublicConvoyDtor(public_convoy_2);
    free(public_convoy_2);

/*---------------- armyminibus display & wash ----------------*/

    army_minibus_ptr = malloc(sizeof(ArmyMinibus));
    ArmyMinibusCtor(army_minibus_ptr);
    army_minibus_ptr->minibus.PubTrans.vptr.display(army_minibus_ptr);
    army_minibus_ptr->minibus.PubTrans.vptr.Wash(army_minibus_ptr, 5);
    ArmyMinibusDtor(army_minibus_ptr);

/*---------------- finish dtors ----------------*/

    SpecialTaxiDtor(&special_taxi);
    
    for(i = 4; i > 0; --i)
    {
        MinibusDtor(&array3[i - 1]);
    }

    /* MinibusDtor(&array3[3]);
    MinibusDtor(&array3[2]);
    MinibusDtor(&array3[1]);
    MinibusDtor(&array3[0]); */

    MinibusDtor(&m2);

    for(i = 3; i > 0; --i)
    {
        PublicTransportDtor(&array2[i - 1]);
    }


    MinibusDtor(&m);
    return 0;
}