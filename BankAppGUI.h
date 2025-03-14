#ifndef BANK_APP_GUI_H
#define BANK_APP_GUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QListWidget>
#include "BANK.h"

class BankAppGUI : public QMainWindow {
Q_OBJECT

public:
    explicit BankAppGUI(QWidget *parent = nullptr);
    ~BankAppGUI() override;

private:
    Bank bank;

    QLabel *balanceLabel;          // Per visualizzare il saldo corrente
    QListWidget *transactionsList; // Per visualizzare l'elenco delle transazioni
    QLineEdit *searchBar;          // Barra di ricerca

    QPushButton *addButton;        // Pulsante per aggiungere transazioni
    QPushButton *deleteButton;     // Pulsante per rimuovere transazioni
    QPushButton *editButton;       // Pulsante per modificare transazioni

    void setupUI();
    void connectSignals();
    void updateBalance();           // Aggiorna la visualizzazione del saldo corrente
    void updateTransactionsList(); // Aggiorna l'elenco delle transazioni

private slots:
    void onAddTransactionClicked();
    void onDeleteTransactionClicked();
    void onEditTransactionClicked();
    void onSearchTextChanged(const QString &text);
};

#endif // BANK_APP_GUI_H
