#include <iostream>


#include <QtTest>

#include <QObject>

#include <QWidget>

#include <QToolBar>

#include <QLineEdit>
#include <QPushButton>


#include <QDialogButtonBox>



#include <QDebug>

#include <QMetaObject>





#include "../../src/OpenSidescan/mainwindow.h"


#define DONT_DO_FIRST_TEST


// https://doc.qt.io/qt-5/qtest-overview.html

class testGUI : public QObject
{
    Q_OBJECT

    // https://www.qtcentre.org/threads/23541-Displaying-GUI-events-with-QtTest
    // If want to show the GUI
    void eventLoop(const int msec);


public slots:
    void InteractWithModalWindowActionImport();

    void InteractWithModalWindowAlreadyAnActiveProject();

    void InteractWithModalWindowToSelectProjectToOpen();

//    void InteractWithModalWindowDialogPlatform();

private slots:

    // The following private slots that are not treated as test functions.


    void initTestCase();        // initTestCase() will be called before the first test function is executed.

//    void initTestCase_data();   // initTestCase_data() will be called to create a global test data table.

    void cleanupTestCase();     // cleanupTestCase() will be called after the last test function was executed.

//    void init();                // init() will be called before each test function is executed.

//    void cleanup();             // cleanup() will be called after every test function.





    // Test functions



#ifndef DONT_DO_FIRST_TEST

    void useToolBarActionImportToLoadSidescanFile();

    void verifyResultOfUseToolBarActionImportToLoadSidescanFile();
#endif



    void useToolBarActionOpenProject();

    void verifyResultOfUseToolBarActionOpenProject();



//    void finish();


//    void TestsvpFileLineEditAndmbesFilePathLineEdit();


//    void TestPuttingValuesOnDialogPlatform();


//    void TestSvpFileBrowse();


//    void finish();




//	void TestSize();

//	void TestClear();

//	void TestConcat_data();
//	void TestConcat();

private:


    MainWindow * mainWindow;
};

void testGUI::eventLoop(const int msec)
{
    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.setSingleShot(true);
    timer.start(msec);
    loop.exec();
}


void testGUI::initTestCase()
{
    mainWindow = nullptr;
}

void testGUI::cleanupTestCase()
{

    std::cout << "\n\n\nBeginning of 'testGUI::cleanupTestCase()'" << std::endl;

    if ( mainWindow ) {
        delete mainWindow;
        mainWindow = nullptr;
    }

}

//void testGUI::init()
//{
////    mainWindow = nullptr;
//}


// Test functions

#ifndef DONT_DO_FIRST_TEST

void testGUI::useToolBarActionImportToLoadSidescanFile()
{


    qDebug() << tr( "Beginning of 'useToolBarActionImportToLoadSidescanFile()'" );

//    mainWindow = nullptr;


    mainWindow = new MainWindow;

    // TODO verify that mainWindow created?


    qDebug() << tr( "list from QApplication::topLevelWidgets()" );

    const QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget *widget : topLevelWidgets) {
        qDebug() << widget->objectName()
                 << ", className: " << widget->metaObject()->className();
    }

    std::cout << "\n\n" << std::endl;

    mainWindow->show();
    eventLoop(2400);


//    std::cout << "Enter something to continue: " << std::endl;

//    std::string textToContinue;

//    std::cin >> textToContinue;


    const QObjectList list = mainWindow->children();

    qDebug() << tr( "mainWindow's object list.size(): " ) << list.size();

    QString actionImportObjectName = tr( "actionImport" );
    QAction * actionImport = nullptr;

    for (QObject *children : list) {
        qDebug() << children->objectName()
                 << ", className: " << children->metaObject()->className();


        if ( children->objectName() == actionImportObjectName )
            actionImport = static_cast<QAction * >( children );


    }

    std::cout << "\n\n" << std::endl;

    mainWindow->show();
    eventLoop(1200);


    QToolBar * mainToolBar = mainWindow->findChild< QToolBar * >( "mainToolBar" );

    const QObjectList listChildrenMainToolBar = mainToolBar->children();

    qDebug() << tr( "listChildrenMainToolBar.size(): " ) << listChildrenMainToolBar.size();

    for (QObject *children : listChildrenMainToolBar) {
        qDebug() << children->objectName()
                 << ", className: " << children->metaObject()->className();
    }


    mainWindow->show();
    eventLoop(1200);

    if ( actionImport != nullptr ) {

        QWidget *widgetForActionImport = mainToolBar->widgetForAction( actionImport );


        QTimer::singleShot(500, this, SLOT(InteractWithModalWindowActionImport() ) );

        // Click the button to open the modal dialog
        QTest::mouseClick(widgetForActionImport, Qt::LeftButton);




    }


}


void testGUI::verifyResultOfUseToolBarActionImportToLoadSidescanFile()
{

    std::cout << "\n\nBeginning of testGUI::verifyResultOfUseToolBarActionImportToLoadSidescanFile\n" << std::endl;

    // Display the number of Sidescan channel tabs (which uses QTabWidget Class)
    std::cout << "\n\nmainWindow->tabs->count(): " << mainWindow->tabs->count() << std::endl;

    // Display the tab labels
    for ( int i=0; i< mainWindow->tabs->count(); i++ ) {
        std::cout << "count: " << i << ", tab text: " << mainWindow->tabs->tabText( i ).toStdString() << "\n";
    }

    std::cout << "\n" << std::endl;





    // Display children QTabWidget

    const QObjectList list = mainWindow->tabs->children();

    qDebug() << tr( "mainWindow->tabs->children() list.size(): " ) << list.size();

    for (QObject *children : list) {
        qDebug() << children->objectName()
                 << ", className: " << children->metaObject()->className();
    }

    std::cout << "\n\n" << std::endl;

//    QTabBar *tabBar = mainWindow->tabs->findChild<QTabBar*>("qt_tabwidget_tabbar");
    QTabBar *tabBar = mainWindow->tabs->tabBar();

    const QObjectList listChildrenTabBar = tabBar->children();

    qDebug() << tr( "tabBar->children() listChildrenTabBar.size(): " ) << listChildrenTabBar.size();

    for (QObject *children : listChildrenTabBar) {
        qDebug() << children->objectName()
                 << ", className: " << children->metaObject()->className();
    }



    std::cout << "\n\ntabBar->count(): " << tabBar->count() << std::endl;

    // Display the tab labels
    for ( int i=0; i< tabBar->count(); i++ ) {
        std::cout << "count: " << i << ", tab text: " << tabBar->tabText( i ).toStdString()
                  << ", tabButton widget address QTabBar::LeftSide: " << tabBar->tabButton(i, QTabBar::LeftSide)
                  << ", tabButton widget address QTabBar::RightSide: " << tabBar->tabButton(i, QTabBar::RightSide)
                  << "\n";
    }


//    std::cout << "\n\n" << std::endl;

    std::cout << "\n\nmainWindow->tabs->currentIndex(): " << mainWindow->tabs->currentIndex() << std::endl;

    // Click on second tab
    int index = 1;
    const QPoint tabPos = tabBar->tabRect( index ).center();
    QTest::mouseClick( tabBar, Qt::LeftButton, {}, tabPos);


    std::cout << "\n\nAfter click on second tab, mainWindow->tabs->currentIndex(): " << mainWindow->tabs->currentIndex() << std::endl;




    mainWindow->show();
    eventLoop(3000);


    // File properties (which uses QTableWidget class)

    std::cout << "\n\nmainWindow->fileInfo->propertiesTable->rowCount(): " << mainWindow->fileInfo->propertiesTable->rowCount() << std::endl;

    for ( int i=0; i< mainWindow->fileInfo->propertiesTable->rowCount(); i++ ) {
        std::cout << "count: " << i << ", \""
                  << mainWindow->fileInfo->propertiesTable->item(i, 0)->text().toStdString()
                  << "\": \"" << mainWindow->fileInfo->propertiesTable->item(i, 1)->text().toStdString()
                  << "\"\n";
    }







//    std::cout << "\n\nWait some time to import file\n" << std::endl;

//    mainWindow->show();
//    eventLoop(20000);

//    // Verify the number of Sidescan channel tabs

//    std::cout << "\n\nmainWindow->tabs->count(): " << mainWindow->tabs->count() << "\n" << std::endl;



//    QVERIFY2(false, "false on purpose" );
//    QVERIFY(false);


    std::cout << "\n\n\nBefore if ( mainWindow )" << std::endl;

    if ( mainWindow ) {
        delete mainWindow;
        mainWindow = nullptr;
    }


}

#endif

void testGUI::useToolBarActionOpenProject()
{
    qDebug() << tr( "Beginning of 'useToolBarActionOpenProject()'" );

    // In case the previous test did not complete to the end
    if ( mainWindow ) {
        delete mainWindow;
        mainWindow = nullptr;
    }


    mainWindow = new MainWindow;

    // TODO verify that mainWindow created?

    mainWindow->show();
    eventLoop(1200);

    QAction * actionOpenProject = mainWindow->findChild< QAction * >( "actionOpenProject" );


    QToolBar * mainToolBar = mainWindow->findChild< QToolBar * >( "mainToolBar" );

    if ( actionOpenProject ) {

        QWidget *widgetForActionOpenProject = mainToolBar->widgetForAction( actionOpenProject );

        QTimer::singleShot(500, this, SLOT(InteractWithModalWindowAlreadyAnActiveProject() ) );

        // Click the button to open the modal dialog
        QTest::mouseClick(widgetForActionOpenProject, Qt::LeftButton);

    }


}

void testGUI::verifyResultOfUseToolBarActionOpenProject()
{

    std::cout << "\n\nBeginning of testGUI::verifyResultOfUseToolBarActionOpenProject()\n" << std::endl;


    mainWindow->show();
    eventLoop(7000);


    QModelIndex currentIndex = mainWindow->projectWindow->tree->currentIndex();

    std::cout << "\n\ncurrentIndex.row(): " << currentIndex.row() << std::endl;


//    // The following does not work to set the current index
//    mainWindow->projectWindow->tree->setCurrentIndex(
//                mainWindow->projectWindow->tree->model()->index( 2, 0 ) );

//    view.setCurrentIndex(view.model()->index(row, column));

    // Click on an item in the treeview
//    QTest::mouseClick(mainWindow->projectWindow->tree->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint( 60, 60) );

//    int xPos = mainWindow->projectWindow->tree->columnViewportPosition(0) + 2; // add 2 pixels
//    int yPos = mainWindow->projectWindow->tree-

    // The following works
//    QTest::mouseClick(mainWindow->projectWindow->tree->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint( 60, 60) );
//    QTest::mouseClick(mainWindow->projectWindow->tree->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint( 60, 5) );


    currentIndex = mainWindow->projectWindow->tree->currentIndex();
    std::cout << "\n\ncurrentIndex.row(): " << currentIndex.row() << std::endl;


    QModelIndexList listSelected = mainWindow->projectWindow->tree->selectionModel()->selectedIndexes();

    std::cout << "\n\nlistSelected.size(): " << listSelected.size() << "\n" << std::endl;



    if ( currentIndex.isValid() ) {
        if ( mainWindow->projectWindow->model->isFilesNode( currentIndex ) == false )
            std::cout << "File name: "
                  << mainWindow->projectWindow->model->data(currentIndex, Qt::DisplayRole).toString().toStdString() << std::endl;
        else
            std::cout << "File node is the current index\n" << std::endl;
    } else { // e.g. no selection
        std::cout << "currentIndex is not valid\n" << std::endl;

    }







    std::cout << "\n\nmainWindow->projectWindow->model->rowCount(): "
              << mainWindow->projectWindow->model->rowCount() << "\n" << std::endl;

    std::cout << "\n\nmainWindow->projectWindow->model->getNbFiles(): "
                 << mainWindow->projectWindow->model->getNbFiles() << "\n"
              << std::endl;



    mainWindow->show();
    eventLoop(10000);


    if ( mainWindow )
    {
        delete mainWindow;
        mainWindow = nullptr;
    }


}





void testGUI::InteractWithModalWindowActionImport()
{
    mainWindow->show();
    eventLoop(1200);


    qDebug() << tr( "After starting ActionImport modal window" );

    QWidget * modalWidget = QApplication::activeModalWidget();
    std::cout << "\n\nmodalWidget: " << modalWidget << "\n" << std::endl;

    qDebug() << tr( "modalWidget->objectName(): " ) << modalWidget->objectName();

    qDebug() << tr( "modalWidget->windowTitle(): " ) << modalWidget->windowTitle();




    std::cout << "\n\n" << std::endl;

    qDebug() << tr( "After starting ActionImport modal window, list from QApplication::topLevelWidgets()" );

    const QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget *widget : topLevelWidgets) {

        if ( modalWidget == widget ) {
            qDebug() << widget->objectName()
                 << ", className: " << widget->metaObject()->className()
                 << tr( " -------- modalWidget == widget --------" );
        } else {
            qDebug() << widget->objectName()
                 << ", className: " << widget->metaObject()->className();
        }

    }


    std::cout << "\n\n" << std::endl;



    const QObjectList list = modalWidget->children();


    QString fileNameEdit = tr( "fileNameEdit" );
    QLineEdit * lineEdit = nullptr;


    qDebug() << tr( "ActionImport modal window list.size(): " ) << list.size();

    for (QObject *children : list) {

        qDebug() << children->objectName()
                 << ", className: " << children->metaObject()->className();



        if ( children->objectName() == fileNameEdit )
            lineEdit = static_cast<QLineEdit * >( children );



    }


    QDialogButtonBox *buttonBox = modalWidget->findChild<QDialogButtonBox*>("buttonBox");


    QList<QAbstractButton *> listButtonBox = buttonBox->buttons();


    std::cout << "\n\n" << std::endl;

    qDebug() << tr( "buttonBox->children() listButtonBox.size(): " ) << listButtonBox.size();

//    QString acceptButtonText = tr( "Select" );

    QString acceptButtonText = tr( "&Open" ); // When using QFileDialog::getOpenFileNames

    QPushButton * acceptButton = nullptr;


    QString cancelButtonText = tr( "&Cancel" );
    QPushButton * cancelButton = nullptr;

    for (QAbstractButton *button : listButtonBox) {

        qDebug() << button->objectName() << ", "
                 << button->text()
                 << ", className: " << button->metaObject()->className();

        if ( button->text() == acceptButtonText )
            acceptButton = static_cast<QPushButton * >( button );
        else if ( button->text() == cancelButtonText )
            cancelButton = static_cast<QPushButton * >( button );

    }



    std::cout << "\n\n" << std::endl;




    QList<QAction *> listActions = modalWidget->actions();


    qDebug() << tr( "modalWidget listActions.size(): " ) << listActions.size();
    for (QAction *action : listActions) {
        qDebug() << action->objectName()
                 << ", className: " << action->metaObject()->className();

    }

    std::cout << "\n\n" << std::endl;

    std::cout << "\n\nmodalWidget->layout(): " << modalWidget->layout();

    std::cout << "\n\n" << std::endl;



    mainWindow->show();
    eventLoop(1200);




    if ( lineEdit != nullptr && acceptButton != nullptr) {


        qDebug() << tr( "lineEdit->text(): " ) << lineEdit->text();


        // Number of characters currently present in the QLineEdit
        int nbBackspaces = lineEdit->text().length();

        qDebug() << tr( "nbBackspaces: " ) << nbBackspaces;

        // Use backspaces to clear the current content
        for ( int count = 0; count < nbBackspaces; count++ )
            QTest::keyClick(lineEdit, Qt::Key_Backspace );


        mainWindow->show();
        eventLoop(1200);


        // Write into input fields
//        QTest::keyClicks(lineEdit, "zxcvbn");



        QTest::keyClicks(lineEdit, "/home/chris/Worskpace/OpenSidescan/test/data/wrecks/plane1.xtf");


//        // Trying to set directly the text
//        lineEdit->setText( "Using setText()" );


        mainWindow->show();
        eventLoop(1200);


        // Click button to close the modal dialog
        QTest::mouseClick(acceptButton, Qt::LeftButton);

        mainWindow->show();
        eventLoop(1200);
    } else if ( cancelButton != nullptr ) {

        // Click button to close the modal dialog
        QTest::mouseClick(cancelButton, Qt::LeftButton);

        mainWindow->show();
        eventLoop(1200);

    }

//    std::cout << "\n\nWait some time to import file\n" << std::endl;

//    mainWindow->show();
//    eventLoop(20000);

//    // Verify the number of Sidescan channel tabs

//    std::cout << "\n\nmainWindow->tabs->count(): " << mainWindow->tabs->count() << "\n" << std::endl;

}


void testGUI::InteractWithModalWindowAlreadyAnActiveProject()
{

    mainWindow->show();
    eventLoop(1200);


    qDebug() << tr( "After starting AlreadyAnActiveProject modal window" );

    QWidget * modalWidget = QApplication::activeModalWidget();
    std::cout << "\n\nmodalWidget: " << modalWidget << "\n" << std::endl;

    qDebug() << tr( "modalWidget->objectName(): " ) << modalWidget->objectName();

    qDebug() << tr( "modalWidget->windowTitle(): " ) << modalWidget->windowTitle();




    std::cout << "\n\n" << std::endl;

    qDebug() << tr( "After starting AlreadyAnActiveProject modal window, list from QApplication::topLevelWidgets()" );

    const QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget *widget : topLevelWidgets) {

        if ( modalWidget == widget ) {
            qDebug() << widget->objectName()
                 << ", className: " << widget->metaObject()->className()
                 << tr( " -------- modalWidget == widget --------" );
        } else {
            qDebug() << widget->objectName()
                 << ", className: " << widget->metaObject()->className();
        }

    }


    std::cout << "\n\n" << std::endl;


    const QObjectList list = modalWidget->children();



    qDebug() << tr( "AlreadyAnActiveProject modal window list.size(): " ) << list.size();

    for (QObject *children : list) {

        qDebug() << children->objectName()
                 << ", className: " << children->metaObject()->className();

    }


    QDialogButtonBox *buttonBox = modalWidget->findChild<QDialogButtonBox*>("qt_msgbox_buttonbox");


    QList<QAbstractButton *> listButtonBox = buttonBox->buttons();


    std::cout << "\n\n" << std::endl;

    qDebug() << tr( "buttonBox->children() listButtonBox.size(): " ) << listButtonBox.size();

    QString OKButtonText = tr( "&OK" );
    QPushButton * buttonOK = nullptr;

    for (QAbstractButton *button : listButtonBox) {

        qDebug() << button->objectName() << ", "
                 << button->text()
                 << ", className: " << button->metaObject()->className();

        if ( button->text() == OKButtonText )
            buttonOK = static_cast<QPushButton * >( button );


    }

    // The buttons don't have objectName.
    //QDEBUG : testGUI::useToolBarActionOpenProject() "" ,  "&OK" , className:  QPushButton
    //QDEBUG : testGUI::useToolBarActionOpenProject() "" ,  "&Cancel" , className:  QPushButton

    std::cout << "\n\n" << std::endl;

    std::cout << "\n\nbuttonOK: " << buttonOK << std::endl;

    QTimer::singleShot(500, this, SLOT(InteractWithModalWindowToSelectProjectToOpen() ) );


    // Click the button to open the modal dialog
    QTest::mouseClick(buttonOK, Qt::LeftButton);



}


void testGUI::InteractWithModalWindowToSelectProjectToOpen()
{
    mainWindow->show();
    eventLoop(1200);

    qDebug() << tr( "Beginning of testGUI::InteractWithModalWindowToSelectProjectToOpen" );

    QWidget * modalWidget = QApplication::activeModalWidget();
    std::cout << "\n\nmodalWidget: " << modalWidget << "\n" << std::endl;

    qDebug() << tr( "modalWidget->objectName(): " ) << modalWidget->objectName();

    qDebug() << tr( "modalWidget->windowTitle(): " ) << modalWidget->windowTitle();




    QLineEdit *lineEdit = modalWidget->findChild<QLineEdit*>("fileNameEdit");




    QDialogButtonBox *buttonBox = modalWidget->findChild<QDialogButtonBox*>("buttonBox");


    QList<QAbstractButton *> listButtonBox = buttonBox->buttons();


    std::cout << "\n\n" << std::endl;

    qDebug() << tr( "buttonBox->children() listButtonBox.size(): " ) << listButtonBox.size();

//    QString acceptButtonText = tr( "Select" );

    QString acceptButtonText = tr( "&Open" ); // When using QFileDialog::getOpenFileNames

    QPushButton * acceptButton = nullptr;


    QString cancelButtonText = tr( "&Cancel" );
    QPushButton * cancelButton = nullptr;

    for (QAbstractButton *button : listButtonBox) {

        qDebug() << button->objectName() << ", "
                 << button->text()
                 << ", className: " << button->metaObject()->className();

        if ( button->text() == acceptButtonText )
            acceptButton = static_cast<QPushButton * >( button );
        else if ( button->text() == cancelButtonText )
            cancelButton = static_cast<QPushButton * >( button );

    }



    std::cout << "\n\n" << std::endl;


    mainWindow->show();
    eventLoop(1200);

    if ( lineEdit != nullptr && acceptButton != nullptr) {


        qDebug() << tr( "lineEdit->text(): " ) << lineEdit->text();


        // Number of characters currently present in the QLineEdit
        int nbBackspaces = lineEdit->text().length();

        qDebug() << tr( "nbBackspaces: " ) << nbBackspaces;

        // Use backspaces to clear the current content
        for ( int count = 0; count < nbBackspaces; count++ )
            QTest::keyClick(lineEdit, Qt::Key_Backspace );


        mainWindow->show();
        eventLoop(1200);

        QTest::keyClicks(lineEdit, "/home/chris/Worskpace/OpenSidescan/test/testProject/TestProject5Files.ssp");


        mainWindow->show();
        eventLoop(1200);


        // Click button to close the modal dialog
        QTest::mouseClick(acceptButton, Qt::LeftButton);

        mainWindow->show();
        eventLoop(1200);
    } else if ( cancelButton != nullptr ) {

        // Click button to close the modal dialog
        QTest::mouseClick(cancelButton, Qt::LeftButton);

        mainWindow->show();
        eventLoop(1200);

    }






}


QTEST_MAIN(testGUI)

#include "testGUI.moc"
