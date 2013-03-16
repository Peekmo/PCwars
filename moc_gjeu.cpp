/****************************************************************************
** Meta object code from reading C++ file 'gjeu.h'
**
** Created: Tue May 8 17:51:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gjeu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gjeu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GJeu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      21,    5,    5,    5, 0x0a,
      38,    5,    5,    5, 0x0a,
      60,    5,    5,    5, 0x0a,
      76,    5,    5,    5, 0x0a,
      93,    5,    5,    5, 0x0a,
      99,    5,    5,    5, 0x0a,
     127,    5,    5,    5, 0x0a,
     140,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GJeu[] = {
    "GJeu\0\0changerImage()\0afficherJoueur()\0"
    "afficherRecrutement()\0effacerDegats()\0"
    "effacerCapture()\0fin()\0"
    "finAffichageTransportRate()\0cacherSoin()\0"
    "afficherFurie()\0"
};

const QMetaObject GJeu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GJeu,
      qt_meta_data_GJeu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GJeu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GJeu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GJeu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GJeu))
        return static_cast<void*>(const_cast< GJeu*>(this));
    return QWidget::qt_metacast(_clname);
}

int GJeu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changerImage(); break;
        case 1: afficherJoueur(); break;
        case 2: afficherRecrutement(); break;
        case 3: effacerDegats(); break;
        case 4: effacerCapture(); break;
        case 5: fin(); break;
        case 6: finAffichageTransportRate(); break;
        case 7: cacherSoin(); break;
        case 8: afficherFurie(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
