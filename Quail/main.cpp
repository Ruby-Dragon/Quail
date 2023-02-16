/*
Copyright (C) 2022 Ruby-Dragon
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator Translator;
    const QStringList UILanguages = QLocale::system().uiLanguages();

    //get languages from language file saved to user's system
    for (const QString &locale : UILanguages)
    {
        //name of translation file to open, all naming files start with Quail_ and are followed by the name of the locale
        //example: Quail_en_US
        const QString baseName = "Quail_" + QLocale(locale).name();

        if (Translator.load(":/i18n/" + baseName)) //if the translation exists (if the language has a ts file in Quail)...
        {
            //... then use it
            app.installTranslator(&Translator);
            break;
        }
    }

    MainWindow window;
    window.show();
    return app.exec();
}
