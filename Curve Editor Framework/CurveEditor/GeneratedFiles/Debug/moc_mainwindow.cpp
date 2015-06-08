/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Sep 28 18:29:45 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      47,   39,   11,   11, 0x08,
      81,   39,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     156,  150,   11,   11, 0x08,
     201,   39,   11,   11, 0x08,
     246,   39,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionAbout_triggered()\0"
    "checked\0on_actionTool_Bar_triggered(bool)\0"
    "on_actionStatus_bar_triggered(bool)\0"
    "on_actionClear_Scene_triggered()\0index\0"
    "on_actionMethod_Choose_ComboBox_Changed(int)\0"
    "on_actionShow_Control_Points_triggered(bool)\0"
    "on_actionShow_Curve_Points_triggered(bool)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionAbout_triggered(); break;
        case 1: on_actionTool_Bar_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: on_actionStatus_bar_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_actionClear_Scene_triggered(); break;
        case 4: on_actionMethod_Choose_ComboBox_Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_actionShow_Control_Points_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: on_actionShow_Curve_Points_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
