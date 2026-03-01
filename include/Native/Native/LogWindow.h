#pragma once
#include <QWidget>
#include <Native/ConsoleOpener.h>
#include <QTextEdit>
#include <QVBoxLayout>


namespace Engine::Native {
    class LogWindow : public QWidget, public NativeLogEvent {
        Q_OBJECT
        ConsoleOpener *console_opener;
        QTextEdit *log_list;
        QVBoxLayout *main_layout;
        QTextCharFormat char_format;
    public:
        explicit LogWindow(QWidget *parent = nullptr, ConsoleOpener* console_opener = nullptr);
        ~LogWindow() override;

        void on_info(const std::string &message) override;
        void closeEvent(QCloseEvent *) override;
    };
}
