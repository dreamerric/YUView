#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QList>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <QTime>
#include <QTreeWidget>
#include <QTimer>
#include <QDesktopWidget>
#include <QKeyEvent>

#include "settingswindow.h"
#include "playlisttreewidget.h"

class PlaylistItem;

#include "displaywidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent( QKeyEvent * event );
    void moveEvent ( QMoveEvent * event );
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    PlaylistTreeWidget *p_playlistWidget;
    Ui::MainWindow *ui;

    QTimer *p_playTimer;
    int p_currentFrame;

    QIcon p_playIcon;
    QIcon p_pauseIcon;
    QIcon p_repeatIcon;
    QIcon p_repeatOnIcon;

    bool p_repeat;
    int p_numFrames;

    QAction *p_leftPanel;
    QAction *p_rightPanel;

    QMessageBox *p_msg;
    QTime p_lastFrameTime;
    int p_FPSCounter;

    int p_cFormatIndex;

public:
    //! loads a list of yuv/xml/csv files
    void loadFiles(QStringList files);

    bool isPlaylistItemSelected() { return selectedPlaylistItem() != NULL; }


public slots:
    //! Toggle fullscreen playback
    void toggleFullscreen();

    //! Shows the file open dialog and loads all selected Files
    void openFile();

    //! Shows file open dialog, loads statistics file and associates it with current selectYUV
    void openStatsFile();

    //! Adds a new text frame
    void addTextFrame();

    //! Starts playback of selected video file
    void play();

    //! Pauses playback of selected video file
    void pause();

    //! Toggles playback of selected video file
    void togglePlayback();

    //! Stops playback of selected video file
    void stop();

    //! Toggle playback in endless loop
    void toggleRepeat();

    //! Deletes a group from playlist
    void deleteItem();

    //! update parameters of regular overlay grid
    void updateGrid();

    //! Select a playlist item as current video for playback
    void setSelectedPlaylistItem(QTreeWidgetItem* newSelectedItem);

    //! Select a Stats Type and update GUI
    void setSelectedStats();

	//! Slot for updating the opacity of the current selected stats type (via items model)
    void updateStatsOpacity(int val);

	//! Slot for updating the grid visibility of the current selected stats type (via items model)
    void updateStatsGrid(bool val);

    //! set current frame for playback
    void setCurrentFrame( int frame, bool forceRefresh = false );

    //! enables the playback controls
    void setControlsEnabled(bool flag);

    //! updates the YUV information GUI elements from the current Renderobject
    void updateMetaInfo();

    //! updates the Playback controls to fit the current YUV settings
    void refreshPlaybackWidgets();

    //! update selection of frame size ComboBox
    void updateFrameSizeComboBoxSelection();

    //! update selection of color format ComboBox
    void updateColorFormatComboBoxSelection(PlaylistItem *selectedItem);

    //! this event is called when the playback-timer is triggered. It will paint the next frame
    void frameTimerEvent();

    void showAbout();

    void bugreport();

    void saveScreenshot();

    void updateSettings();
private slots:
    //! Timeout function for playback timer
    //void newFrameTimeout();

    void statsTypesChanged();

    void on_interpolationComboBox_currentIndexChanged(int index);
    void on_colorFormatComboBox_currentIndexChanged(int index);
    void on_sizeComboBox_currentIndexChanged(int index);

private:
    int findMaxNumFrames();
    PlaylistItem* selectedPlaylistItem();

    static QVector<StatisticsRenderItem> p_emptyTypes;
    SettingsWindow p_settingswindow;
};

#endif // MAINWINDOW_H