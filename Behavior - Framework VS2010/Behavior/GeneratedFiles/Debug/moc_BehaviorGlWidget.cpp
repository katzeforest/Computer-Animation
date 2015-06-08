/****************************************************************************
** Meta object code from reading C++ file 'BehaviorGlWidget.h'
**
** Created: Sat Nov 29 12:07:20 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BehaviorGlWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BehaviorGlWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BehaviorGlWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      45,   37,   17,   17, 0x0a,
      87,   17,   17,   17, 0x0a,
     120,   37,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BehaviorGlWidget[] = {
    "BehaviorGlWidget\0\0on_timer_timeout()\0"
    "checked\0on_actionShowControlPanel_triggered(bool)\0"
    "on_actionResetCamera_triggered()\0"
    "on_actionPlay_triggered(bool)\0"
};

const QMetaObject BehaviorGlWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_BehaviorGlWidget,
      qt_meta_data_BehaviorGlWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BehaviorGlWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BehaviorGlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BehaviorGlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BehaviorGlWidget))
        return static_cast<void*>(const_cast< BehaviorGlWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int BehaviorGlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_timer_timeout(); break;
        case 1: on_actionShowControlPanel_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: on_actionResetCamera_triggered(); break;
        case 3: on_actionPlay_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
