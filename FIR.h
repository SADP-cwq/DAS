#ifndef FIR_H
#define FIR_H

class CFilter_FIR
{
public:
    CFilter_FIR();
    virtual ~CFilter_FIR();
private:
    double *m_pB;

    double *m_pdata_buf;

    int m_nB_order;

    int m_nFirIndex;
public:
    void reset();

    /*brief:×¢Òâ£ºBÊý×éÎªnB_order¸ö
    */
    void setPara(double B[], int nB_order);

    double filter(double data);
    void filter(double data[], int len);
    void filter(double data_in[], double data_out[], int len);

};

inline CFilter_FIR::CFilter_FIR()
{
    m_pB = 0;
    m_pdata_buf = 0;
    m_nB_order = 0;

    m_nFirIndex = 0;
}

inline CFilter_FIR::~CFilter_FIR()
{
    if (m_pdata_buf)
    {
        delete m_pdata_buf;
        m_pdata_buf = 0;
    }
    if (m_pB)
    {
        delete m_pB;
        m_pB = 0;
    }
}

inline void CFilter_FIR::reset()
{
    for(int i = 0; i < m_nB_order; i++)
    {
        m_pdata_buf[i] = 0.0;
    }
    m_nFirIndex = 0;
}


inline void CFilter_FIR::setPara(double B[], int nB_order)
{
    m_nB_order = nB_order;

    if (m_pB)
    {
        delete m_pB;
    }
    if (m_pdata_buf)
    {
        delete m_pdata_buf;
    }

    m_pB = new double[nB_order ];
    m_pdata_buf = new double[nB_order ];

    for(int i = 0; i < nB_order; i++)
    {
        m_pB[i] = B[i];
        m_pdata_buf[i] = 0.0;
    }
}


inline double CFilter_FIR::filter(double data)
{
    int k;
    double fOut = 0.0;

    int i = 0;
    m_pdata_buf[m_nFirIndex%m_nB_order] = data;
    fOut = 0.0f;

    for (i = 0; i < m_nB_order; ++i)
    {
        fOut += m_pdata_buf[(m_nFirIndex +i+1)%m_nB_order]*m_pB[i];
    }

    m_nFirIndex++;
    return fOut;
}



inline void CFilter_FIR::filter(double data[], int len)
{
   int k;
   double fOut = 0.0;
    for(k = 0; k < len; k++)
    {
        int i = 0;
        m_pdata_buf[m_nFirIndex%m_nB_order] = data[k];
        fOut = 0.0f;

        for (i = 0; i < m_nB_order; ++i)
        {
            fOut += m_pdata_buf[(m_nFirIndex +i+1)%m_nB_order]*m_pB[i];
        }
        m_nFirIndex++;

        data[k] = fOut;

    }
}

inline void CFilter_FIR::filter(double data_in[], double data_out[], int len)
{
    int k;
    for(k = 0; k < len; k++)
    {
        int i = 0;
        m_pdata_buf[m_nFirIndex%m_nB_order] = data_in[k];
        data_out[k] = 0.0f;

        for (i = 0; i < m_nB_order; ++i)
        {
            data_out[k] += m_pdata_buf[(m_nFirIndex +i+1)%m_nB_order]*m_pB[i];
        }
        m_nFirIndex++;
    }
}

#endif // FIR_H
