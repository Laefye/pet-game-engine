#pragma once
#include <QWidget>
#include <Native/ConsoleOpener.h>
#include <QListWidget>
#include <QVBoxLayout>


namespace Engine::Native {
    class LogWindow : public QWidget, public NativeLogEvent {
        Q_OBJECT
        ConsoleOpener *console_opener;
        QListWidget *log_list;
        QVBoxLayout *main_layout;
    public:
        explicit LogWindow(QWidget *parent = nullptr, ConsoleOpener* console_opener = nullptr);
        ~LogWindow() override;

        void on_info(const std::string &message) override;
        void closeEvent(QCloseEvent *) override;
    };
}
