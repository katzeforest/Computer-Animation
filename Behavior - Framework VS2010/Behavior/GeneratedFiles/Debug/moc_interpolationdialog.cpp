/****************************************************************************
** Meta object code from reading C++ file 'interpolationdialog.h'
**
** Created: Sat Nov 29 12:07:21 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interpolationdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interpolationdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InterpolationDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      51,   45,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InterpolationDialog[] = {
    "InterpolationDialog\0\0on_buttonBox_accepted()\0"
    "index\0on_comboBox_type_currentIndexChanged(int)\0"
};

const QMetaObject InterpolationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InterpolationDialog,
      qt_meta_data_InterpolationDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InterpolationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InterpolationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InterpolationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InterpolationDialog))
        return static_cast<void*>(const_cast< InterpolationDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InterpolationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_buttonBox_accepted(); break;
        case 1: on_comboBox_type_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
