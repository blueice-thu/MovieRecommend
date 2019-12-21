#include "movie.h"
#include "ui_movie.h"

Movie::Movie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Movie)
{
    ui->setupUi(this);
    setWindowTitle("电影检索与推荐");
    setFixedSize(1050, 650);

    ui->searchButton->setShortcut(Qt::Key_Enter);
    ui->searchButton->setShortcut(Qt::Key_Return);
    ui->title1->installEventFilter(this);
    ui->title1_2->installEventFilter(this);
    ui->title1_3->installEventFilter(this);
    ui->title1_4->installEventFilter(this);
    ui->title1_5->installEventFilter(this);

    infoFileList = nullptr;
    resultList = nullptr;

    initUI();
    initDict();
}

Movie::~Movie()
{
    delete ui;
    delete dict;
    if (infoFileList)
        delete infoFileList;
    if (resultList)
        delete resultList;
}

void Movie::initUI()
{
    ui->content->setText("");
    ui->title1->setText("");
    ui->title1_2->setText("");
    ui->title1_3->setText("");
    ui->title1_4->setText("");
    ui->title1_5->setText("");

    ui->recom_1->setText("");
    ui->recom_2->setText("");
    ui->recom_3->setText("");
    ui->recom_4->setText("");
    ui->recom_5->setText("");
}

void Movie::initDict()
{
    // Load dictionary from the given file .dic
    char dictPath[] = ".\\dictionary\\mydict.dic";
    dict = new BalancedBinaryTree();
    LoadDict(dict, dictPath);

    // Get all .txt file name
    char txtPathName[] = ".\\input\\";
    char txtFormat[] = ".txt";
    CharStringLink* txtFileList = new CharStringLink();
    GetFileList(txtFileList, txtPathName, txtFormat);

    // Build document list
    BaseCharString* pTxtList = txtFileList->getBase()->next;
    while (pTxtList != nullptr)
    {
        char txtNameTemp[40];
        pTxtList->data->toChar(txtNameTemp);
        int docID = CharToInt(txtNameTemp);
        char wordTemp[40];
        ifstream readTxt(txtNameTemp);
        while (readTxt.getline(wordTemp, 40))
        {
            dict->UpdateNode(wordTemp, docID);
        }
        readTxt.close();
        pTxtList = pTxtList->next;
    }
}

void Movie::readKeyWord()
{
    initUI();
    char* sentTemp = nullptr;
    QByteArray ba = ui->inputLine->text().toUtf8();
    sentTemp = ba.data();
    // Read a line
    size_t lenSent = strlen(sentTemp);
    if (lenSent == 0)
        return;
    if (resultList)
    {
        delete resultList;
        resultList = nullptr;
    }
    resultList = new DocList();
    for (size_t i = 0; i < lenSent; i++)
    {
        while (sentTemp[i] == ' ')
            i++;
        if (i >= lenSent)
            break;

        // Read a word
        char aWord[50] = { '\0' };
        size_t end = i + 1;
        while (end < lenSent && sentTemp[end] != ' ')
            end++; // The position of space
        for (size_t j = 0; i + j < end; j++)
        {
            aWord[j] = sentTemp[i + j];
        }
        i = end;

        // Get document list of aWord
        PNode re = dict->SearchNode(aWord);
        doc* reDoc = nullptr;
        if (re)
            reDoc = re->article->Head();
        while (reDoc)
        {
            resultList->Add(reDoc);
            reDoc = reDoc->next;
        }
    }
    resultList->Sort();
    // Write result to outfile
    doc* temp = resultList->Head();
    size_t index = 0;
    ifstream readInfo;
    while (index < 5 && temp != nullptr)
    {
        char infofile[60] = "input\\";
        char c[50] = {'\0'};
        IdToInfo(temp->docID, c);
        strcat(infofile, c);
        readInfo.open(infofile);
        if (readInfo.fail())
        {
            qDebug() << "No id found!";
            exit(0);
        }
        char re[100] = {'\0'};
        readInfo.getline(re, 100);

        if (index == 0)
        {
            ui->title1->setText(re);
            ui->title1->show();
        }
        else if (index == 1)
        {
            ui->title1_2->setText(re);
            ui->title1_2->show();
        }
        else if (index == 2)
        {
            ui->title1_3->setText(re);
            ui->title1_3->show();
        }
        else if (index == 3)
        {
            ui->title1_4->setText(re);
            ui->title1_4->show();
        }
        else if (index == 4)
        {
            ui->title1_5->setText(re);
            ui->title1_5->show();
        }
        index++;
        temp = temp->next;
        readInfo.close();
    }
//    if (sentTemp)
//        delete[] sentTemp;
}

bool Movie::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == ui->title1)
    {
        if (ui->title1->text().isEmpty())
            return QWidget::eventFilter(watched, event);
        if (event->type() == QEvent::MouseButtonPress)
        {
            showDetail(ui->title1);
            if (!resultList)
                return QWidget::eventFilter(watched, event);
            doc* pDoc = resultList->Head();
            char title[100] = {'\0'};
            IdToInfo(pDoc->docID, title);
            InfoToTxt(title);
            showRecom(title);
        }
    }
    else if (watched == ui->title1_2)
    {
        if (ui->title1_2->text().isEmpty())
            return QWidget::eventFilter(watched, event);
        if (event->type() == QEvent::MouseButtonPress)
        {
            showDetail(ui->title1_2);
            if (!resultList)
                return QWidget::eventFilter(watched, event);
            doc* pDoc = resultList->Head()->next;
            char title[100] = {'\0'};
            IdToInfo(pDoc->docID, title);
            InfoToTxt(title);
            showRecom(title);
        }
    }
    else if (watched == ui->title1_3)
    {
        if (ui->title1_3->text().isEmpty())
            return QWidget::eventFilter(watched, event);
        if (event->type() == QEvent::MouseButtonPress)
        {
            showDetail(ui->title1_3);
            if (!resultList)
                return QWidget::eventFilter(watched, event);
            doc* pDoc = resultList->Head()->next->next;
            char title[100] = {'\0'};
            IdToInfo(pDoc->docID, title);
            InfoToTxt(title);
            showRecom(title);
        }
    }
    else if (watched == ui->title1_4)
    {
        if (ui->title1_4->text().isEmpty())
            return QWidget::eventFilter(watched, event);
        if (event->type() == QEvent::MouseButtonPress)
        {
            showDetail(ui->title1_4);
            if (!resultList)
                return QWidget::eventFilter(watched, event);
            doc* pDoc = resultList->Head()->next->next->next;
            char title[100] = {'\0'};
            IdToInfo(pDoc->docID, title);
            InfoToTxt(title);
            showRecom(title);
        }
    }
    else if (watched == ui->title1_5)
    {
        if (ui->title1_5->text().isEmpty())
            return QWidget::eventFilter(watched, event);
        if (event->type() == QEvent::MouseButtonPress)
        {
            showDetail(ui->title1_5);
            if (!resultList)
                return QWidget::eventFilter(watched, event);
            doc* pDoc = resultList->Head()->next->next->next->next;
            char title[100] = {'\0'};
            IdToInfo(pDoc->docID, title);
            InfoToTxt(title);
            showRecom(title);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Movie::showDetail(QLabel* title)
{
    ui->content->setText("");

    char* titleTemp = nullptr;
    QByteArray ba = title->text().toUtf8();
    titleTemp = ba.data();

    if (infoFileList == nullptr)
    {
        infoFileList = new CharStringLink();
        GetFileList(infoFileList, "input\\", ".info");
    }
    ifstream readInfo;
    BaseCharString* pInfoList = infoFileList->getBase()->next;
    char infoTitle[100] = { '\0' }; // the movie name
    char infoName[40] = { '\0' }; // the .info file name
    bool find = false;
    while (pInfoList)
    {
        pInfoList->data->toChar(infoName);
        readInfo.open(infoName);
        readInfo.getline(infoTitle, 50);
        readInfo.close();

        // Find given aim movie
        bool same = true;
        if (titleTemp[0] != infoTitle[0] || titleTemp[1] != infoTitle[1])
            same = false;
        else
        {
            size_t len1 = strlen(titleTemp);
            size_t len2 = strlen(infoTitle);
            len1 = len1 <= len2 ? len1 : len2;
            for (size_t i = 0; i < len1; i++)
            {
                if (titleTemp[i] != infoTitle[i])
                {
                    same = false;
                    break;
                }
                else if (titleTemp[i] == ' ' || infoTitle[i] == ' ')
                    break;
            }
        }

        if (same)
        {
            readInfo.open(infoName);
            stringstream buffer;
            buffer << readInfo.rdbuf();
            string content(buffer.str());
            ui->content->setText(buffer.str().c_str());
            readInfo.close();
            find = true;
            break;
        }
        else
        {
            pInfoList = pInfoList->next;
        }
    }
    if (!find)
    {
        ui->content->setText(u8"该电影不在数据库中，无法推荐");
        return;
    }

}

void Movie::showRecom(char* txtName)
{
    ifstream readTxt;
    char fullname[100] = "input\\";
    strcat(fullname, txtName);
    readTxt.open(fullname);
    if (readTxt.fail())
    {
        qDebug() << "Open TXT fail";
        return;
    }
    DocList* recomList = new DocList();
    char txtTemp[100] = { '\0' };
    while (readTxt.getline(txtTemp, 100))
    {
        PNode re = dict->SearchNode(txtTemp);
        doc* reDoc = nullptr;
        if (re)
            reDoc = re->article->Head();
        while (reDoc)
        {
            recomList->Add(reDoc);
            reDoc = reDoc->next;
        }
    }
    recomList->Sort();

    // Get movie name, skip the first one
    doc* pDoc = recomList->Head()->next;
    ifstream readInfo;
    for (int i = 0; i < 5; i++)
    {
        if (!pDoc)
            break;

        char path[100] = u8".\\input\\";

        char filename[100] = { '\0' };
        IdToInfo(pDoc->docID, filename);
        strcat(path, filename);

        readInfo.open(path);
        char moviename[100] = { '\0' };
        readInfo.getline(moviename, 100);

        size_t j = 0;
        while (moviename[j] != ' ')
            j++;
        while (j < strlen(moviename))
            moviename[j++] = '\0';
        if (i == 0)
        {
            ui->recom_1->setText(moviename);
        }
        else if (i == 1)
        {
            ui->recom_2->setText(moviename);
        }
        else if (i == 2)
        {
            ui->recom_3->setText(moviename);
        }
        else if (i == 3)
        {
            ui->recom_4->setText(moviename);
        }
        else if (i == 4)
        {
            ui->recom_5->setText(moviename);
        }

        readInfo.close();
        pDoc = pDoc->next;
    }
    delete recomList;
}

void Movie::on_searchButton_clicked()
{
    readKeyWord();
}
