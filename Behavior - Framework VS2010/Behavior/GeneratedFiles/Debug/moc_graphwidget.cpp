/****************************************************************************
** Meta object code from reading C++ file 'graphwidget.h'
**
** Created: Sat Nov 29 12:07:20 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      23,   12,   12,   12, 0x0a,
      32,   12,   12,   12, 0x0a,
      42,   12,   12,   12, 0x0a,
      81,   75,   12,   12, 0x0a,
     138,  130,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphWidget[] = {
    "GraphWidget\0\0shuffle()\0zoomIn()\0"
    "zoomOut()\0on_actionClear_Scene_triggered()\0"
    "index\0on_methodChooseComboBox_currentIndexChanged(int)\0"
    "checked\0on_actionShow_Control_Points_triggered(bool)\0"
};

const QMetaObject GraphWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphWidget,
      qt_meta_data_GraphWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphWidget))
        return static_cast<void*>(const_cast< GraphWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: shuffle(); break;
        case 1: zoomIn(); break;
        case 2: zoomOut(); break;
        case 3: on_actionClear_Scene_triggered(); break;
        case 4: on_methodChooseComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_actionShow_Control_Points_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
