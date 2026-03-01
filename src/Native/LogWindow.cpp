#include <Native/LogWindow.h>
#include <QDebug>

namespace Engine::Native {
    LogWindow::LogWindow(QWidget *parent, ConsoleOpener* console_opener) : QWidget(parent), console_opener(console_opener) {
        setWindowTitle("Console");
        resize(400, 300);

        main_layout = new QVBoxLayout();
        setLayout(main_layout);
        log_list = new QTextEdit();
        log_list->setReadOnly(true);
        main_layout->addWidget(log_list);

        console_opener->get_log_bus()->subscribe(this);
    }

    LogWindow::~LogWindow() {
        console_opener->get_log_bus()->unsubscribe(this);
    }

    void LogWindow::on_info(const std::string &message) {
        char_format.setForeground(QColor("cyan"));
        log_list->setCurrentCharFormat(char_format);
        log_list->append("[INFO] -> " + QString::fromStdString(message));
    }

    void LogWindow::closeEvent(QCloseEvent *) {
        console_opener->close_console();
    }
}
