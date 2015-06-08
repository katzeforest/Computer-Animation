/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created: Sat Nov 29 12:07:20 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../glwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      36,    9,    9,    9, 0x0a,
      62,    9,    9,    9, 0x0a,
      93,    9,    9,    9, 0x0a,
     132,  124,    9,    9, 0x0a,
     163,    9,    9,    9, 0x0a,
     197,    9,    9,    9, 0x0a,
     223,    9,    9,    9, 0x0a,
     254,  248,    9,    9, 0x0a,
     304,  124,    9,    9, 0x0a,
     335,  124,    9,    9, 0x0a,
     363,    9,    9,    9, 0x0a,
     393,    9,    9,    9, 0x0a,
     420,    9,    9,    9, 0x0a,
     447,    9,    9,    9, 0x0a,
     480,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWidget[] = {
    "GLWidget\0\0on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionPlay_Back_triggered()\0"
    "on_actionStep_Back_triggered()\0checked\0"
    "on_actionPause_triggered(bool)\0"
    "on_actionStep_Forward_triggered()\0"
    "on_actionPlay_triggered()\0"
    "on_slider_valueChanged()\0index\0"
    "on_comboBoxSwitch_Motion_currentIndexChanged(int)\0"
    "on_actionCoord_triggered(bool)\0"
    "on_actionIK_triggered(bool)\0"
    "on_actionSkeleton_triggered()\0"
    "on_actionApply_triggered()\0"
    "on_actionBlend_triggered()\0"
    "on_actionResetCamera_triggered()\0"
    "on_timer_timeout()\0"
};

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget,
      qt_meta_data_GLWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionOpen_triggered(); break;
        case 1: on_actionSave_triggered(); break;
        case 2: on_actionPlay_Back_triggered(); break;
        case 3: on_actionStep_Back_triggered(); break;
        case 4: on_actionPause_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: on_actionStep_Forward_triggered(); break;
        case 6: on_actionPlay_triggered(); break;
        case 7: on_slider_valueChanged(); break;
        case 8: on_comboBoxSwitch_Motion_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: on_actionCoord_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: on_actionIK_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: on_actionSkeleton_triggered(); break;
        case 12: on_actionApply_triggered(); break;
        case 13: on_actionBlend_triggered(); break;
        case 14: on_actionResetCamera_triggered(); break;
        case 15: on_timer_timeout(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
