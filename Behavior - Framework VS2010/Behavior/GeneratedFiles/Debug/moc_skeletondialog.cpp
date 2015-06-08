/****************************************************************************
** Meta object code from reading C++ file 'skeletondialog.h'
**
** Created: Sat Nov 29 12:07:22 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../skeletondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skeletondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkeletonDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   16,   15,   15, 0x08,
     102,   15,   15,   15, 0x08,
     139,   15,   15,   15, 0x08,
     176,   15,   15,   15, 0x08,
     213,   15,   15,   15, 0x08,
     250,   15,   15,   15, 0x08,
     287,   15,   15,   15, 0x08,
     324,   15,   15,   15, 0x08,
     346,   15,   15,   15, 0x08,
     372,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SkeletonDialog[] = {
    "SkeletonDialog\0\0selected,deselected\0"
    "on_selectionModel_selectionChanged(QItemSelection,QItemSelection)\0"
    "on_doubleSpinBoxRx_editingFinished()\0"
    "on_doubleSpinBoxRy_editingFinished()\0"
    "on_doubleSpinBoxRz_editingFinished()\0"
    "on_doubleSpinBoxTx_editingFinished()\0"
    "on_doubleSpinBoxTy_editingFinished()\0"
    "on_doubleSpinBoxTz_editingFinished()\0"
    "on_buttonOK_clicked()\0on_buttonCancel_clicked()\0"
    "on_buttonApply_clicked()\0"
};

const QMetaObject SkeletonDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SkeletonDialog,
      qt_meta_data_SkeletonDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkeletonDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkeletonDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkeletonDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkeletonDialog))
        return static_cast<void*>(const_cast< SkeletonDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SkeletonDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_selectionModel_selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 1: on_doubleSpinBoxRx_editingFinished(); break;
        case 2: on_doubleSpinBoxRy_editingFinished(); break;
        case 3: on_doubleSpinBoxRz_editingFinished(); break;
        case 4: on_doubleSpinBoxTx_editingFinished(); break;
        case 5: on_doubleSpinBoxTy_editingFinished(); break;
        case 6: on_doubleSpinBoxTz_editingFinished(); break;
        case 7: on_buttonOK_clicked(); break;
        case 8: on_buttonCancel_clicked(); break;
        case 9: on_buttonApply_clicked(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
