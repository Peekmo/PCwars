/****************************************************************************
** Meta object code from reading C++ file 'fenetre.h'
**
** Created: Tue May 8 17:51:17 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fenetre.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fenetre[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      28,    8,    8,    8, 0x05,
      41,    8,    8,    8, 0x05,
      57,    8,    8,    8, 0x05,
      70,    8,    8,    8, 0x05,
      89,    8,    8,    8, 0x05,
     101,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     113,    8,    8,    8, 0x08,
     131,    8,    8,    8, 0x08,
     146,    8,    8,    8, 0x08,
     161,    8,    8,    8, 0x08,
     175,    8,    8,    8, 0x08,
     196,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Fenetre[] = {
    "Fenetre\0\0fermetureFenetre()\0retourMenu()\0"
    "envoieOptions()\0envoieInit()\0"
    "envoieChargement()\0envoieJeu()\0"
    "envoieFin()\0afficherOptions()\0"
    "afficherMenu()\0afficherInit()\0"
    "afficherJeu()\0afficherChargement()\0"
    "finJeu()\0"
};

const QMetaObject Fenetre::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Fenetre,
      qt_meta_data_Fenetre, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fenetre::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fenetre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fenetre::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fenetre))
        return static_cast<void*>(const_cast< Fenetre*>(this));
    return QWidget::qt_metacast(_clname);
}

int Fenetre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fermetureFenetre(); break;
        case 1: retourMenu(); break;
        case 2: envoieOptions(); break;
        case 3: envoieInit(); break;
        case 4: envoieChargement(); break;
        case 5: envoieJeu(); break;
        case 6: envoieFin(); break;
        case 7: afficherOptions(); break;
        case 8: afficherMenu(); break;
        case 9: afficherInit(); break;
        case 10: afficherJeu(); break;
        case 11: afficherChargement(); break;
        case 12: finJeu(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Fenetre::fermetureFenetre()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Fenetre::retourMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Fenetre::envoieOptions()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Fenetre::envoieInit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Fenetre::envoieChargement()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Fenetre::envoieJeu()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Fenetre::envoieFin()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
