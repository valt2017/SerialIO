// simulator3Doc.h : Schnittstelle der Klasse CSimulator3Doc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATOR3DOC_H__211FB421_1C62_491E_B684_D7FCD29571C8__INCLUDED_)
#define AFX_SIMULATOR3DOC_H__211FB421_1C62_491E_B684_D7FCD29571C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimulator3Doc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CSimulator3Doc();
	DECLARE_DYNCREATE(CSimulator3Doc)

// Attribute
public:
	CStringArray m_stringArray;
// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSimulator3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementierung
public:
	void GetInputs(void);
	virtual ~CSimulator3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CSimulator3Doc)
	afx_msg void OnAlarmschalter();
	afx_msg void OnAuszugbnp();
	afx_msg void OnBnp();
	afx_msg void OnMunzkassette();
	afx_msg void OnRestgeldwagen();
	afx_msg void OnRiegelstange();
	afx_msg void OnTurkontakt();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_SIMULATOR3DOC_H__211FB421_1C62_491E_B684_D7FCD29571C8__INCLUDED_)
