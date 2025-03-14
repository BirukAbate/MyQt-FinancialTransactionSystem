#include "BankAppGUI.h"
#include <QMessageBox>
#include <QInputDialog>

BankAppGUI::BankAppGUI(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    connectSignals();
    updateBalance();
    updateTransactionsList();
}

BankAppGUI::~BankAppGUI() = default;

void BankAppGUI::setupUI() {
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);

    // Etichetta per il saldo corrente
    balanceLabel = new QLabel("Current Balance: $0.00", this);
    balanceLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(balanceLabel);

    // Lista per visualizzare le transazioni
    transactionsList = new QListWidget(this);
    mainLayout->addWidget(transactionsList);

    // Barra di ricerca
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search by name or date...");
    mainLayout->addWidget(searchBar);

    // Layout orizzontale per i pulsanti
    auto *buttonLayout = new QHBoxLayout();

    addButton = new QPushButton("+", this);
    deleteButton = new QPushButton("-", this);
    editButton = new QPushButton("✎", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("Bank UniFi");
    resize(600, 400);
}

void BankAppGUI::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &BankAppGUI::onAddTransactionClicked);
    connect(deleteButton, &QPushButton::clicked, this, &BankAppGUI::onDeleteTransactionClicked);
    connect(editButton, &QPushButton::clicked, this, &BankAppGUI::onEditTransactionClicked);
    connect(searchBar, &QLineEdit::textChanged, this, &BankAppGUI::onSearchTextChanged);
}

void BankAppGUI::updateBalance() {
    balanceLabel->setText(QString("Current Balance: $%1").arg(bank.getCurrentBalance(), 0, 'f', 2));
}

void BankAppGUI::updateTransactionsList() {
    transactionsList->clear();
    for (int i = 0; i < bank.getTotalTransactions(); ++i) {
        const auto &transaction = bank.getTransaction(i);
        transactionsList->addItem(QString("%1 | $%2 | %3")
                                          .arg(QString::fromStdString(transaction.getName()))
                                          .arg(transaction.getAmount(), 0, 'f', 2)
                                          .arg(QString::fromStdString(transaction.getDate())));
    }
}

void BankAppGUI::onAddTransactionClicked() {
    bool ok;

    // Nome transazione
    QString name = QInputDialog::getText(this, "Add Transaction", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    // Selezione tipo transazione (Income o Expense)
    QStringList types = {"Income (+)", "Expense (-)"};
    QString type = QInputDialog::getItem(this, "Transaction Type", "Select type:", types, 0, false, &ok);
    if (!ok) return;

    // Importo transazione
    double amount = QInputDialog::getDouble(this, "Add Transaction", "Amount:", 0, 0, 10000, 2, &ok);
    if (!ok) return;

    // Se il tipo è "Expense (-)", rendiamo l'importo negativo
    if (type == "Expense (-)") {
        amount = -amount;
    }

    // Data transazione
    QString date = QInputDialog::getText(this, "Add Transaction", "Date (YYYY-MM-DD):", QLineEdit::Normal, "", &ok);
    if (!ok || date.isEmpty()) return;

    try {
        bank.addTransaction(name.toStdString(), amount, date.toStdString());
        QMessageBox::information(this, "Success", "Transaction added successfully!");
        updateBalance();
        updateTransactionsList();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}


void BankAppGUI::onDeleteTransactionClicked() {
    auto selectedItem = transactionsList->currentRow();
    if (selectedItem == -1) {
        QMessageBox::warning(this, "Error", "Please select a transaction to delete.");
        return;
    }

    bank.deleteTransaction(selectedItem);
    QMessageBox::information(this, "Success", "Transaction deleted successfully!");
    updateBalance();
    updateTransactionsList();
}

void BankAppGUI::onEditTransactionClicked() {
    auto selectedItem = transactionsList->currentRow();
    if (selectedItem == -1) {
        QMessageBox::warning(this, "Error", "Please select a transaction to edit.");
        return;
    }

    bool ok;
    QString newName = QInputDialog::getText(this, "Edit Transaction", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || newName.isEmpty()) return;

    QString newAmountStr = QInputDialog::getText(this, "Edit Transaction", "Amount:", QLineEdit::Normal, "", &ok);
    if (!ok || newAmountStr.isEmpty()) return;
    double newAmount = newAmountStr.toDouble();

    QString newDate = QInputDialog::getText(this, "Edit Transaction", "Date (YYYY-MM-DD):", QLineEdit::Normal, "", &ok);
    if (!ok || newDate.isEmpty()) return;

    try {
        bank.editTransaction(selectedItem, newName.toStdString(), newAmount, newDate.toStdString());
        QMessageBox::information(this, "Success", "Transaction edited successfully!");
        updateBalance();
        updateTransactionsList();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void BankAppGUI::onSearchTextChanged(const QString &text) {
    transactionsList->clear();
    for (int i = 0; i < bank.getTotalTransactions(); ++i) {
        const auto &transaction = bank.getTransaction(i);
        if (QString::fromStdString(transaction.getName()).contains(text, Qt::CaseInsensitive) ||
            QString::fromStdString(transaction.getDate()).contains(text, Qt::CaseInsensitive)) {
            transactionsList->addItem(QString("%1 | $%2 | %3")
                                              .arg(QString::fromStdString(transaction.getName()))
                                              .arg(transaction.getAmount(), 0, 'f', 2)
                                              .arg(QString::fromStdString(transaction.getDate())));
        }
    }
}
