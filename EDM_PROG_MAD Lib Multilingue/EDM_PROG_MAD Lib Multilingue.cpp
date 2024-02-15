#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Definim un alias per a l'unordered_map que emmagatzemarà les traduccions
using TraduccionsMap = unordered_map<string, string>;

// Funció per llegir el fitxer de traduccions i emmagatzemar-les en un unordered_map
TraduccionsMap llegirFitxerTraduccions(const string& Traduccio) {
    TraduccionsMap traduccions;
    ifstream fitxer(Traduccio);
    if (!fitxer) {
        cerr << "Error en obrir el fitxer de traduccions: " << Traduccio << endl;
        return traduccions; // Retornem un map buit en cas d'error
    }

    string linia;
    while (getline(fitxer, linia)) {
        size_t pos = linia.find(' ');
        if (pos != string::npos) {
            string clau = linia.substr(0, pos);
            string valor = linia.substr(pos + 1);
            traduccions[clau] = valor;
        }
       
    }

    fitxer.close();
    return traduccions;
}

// Funció per mostrar un text utilitzant les traduccions proporcionades
void mostrarText(const string& text, const TraduccionsMap& traduccions) {
    auto it = traduccions.find(text);
    if (it != traduccions.end()) {
        cout << it->second << endl;
    }
    else {
        cout << "Traducció no disponible per aquest idioma." << endl;
    }
}

// Funció per validar si un idioma és vàlid
bool idiomaValid(const string& idioma) {
    // Llista d'idiomes vàlids
    const vector<string> idiomes_valids = { "CA", "EU", "GL", "OC", "ES", "EN", "FR", "DE", "IT", "PT", "NL", "SV", "PL", "DA" };
    // Comprovació si l'idioma és a la llista d'idiomes vàlids
    return find(idiomes_valids.begin(), idiomes_valids.end(), idioma) != idiomes_valids.end();
}

/// <summary>
/// Sol·licita a l'usuari una entrada de text i retorna el text introduït.s
/// </summary>
/// <param name="prompt">Pregunta a fer  l'usuari.</param>
/// <returns>retorna la resposta en forma de paraula </returns>
string demanarText(string prompt)
{
    string resposta;
    cout << prompt;
    getline(cin, resposta);
    return resposta;
}

/// <summary>
/// Sol·licita a l'usuari una entrada numèrica i retorna el número introduït.
/// </summary>
/// <param name="prompt">Pregunta a fer  l'usuari..</param>
/// <returns>retorna la resposta en forma de paraula.</returns>
int demanarNumero(string prompt)
{
    int resposta;
    cout << prompt;
    cin >> resposta;
    return resposta;
}

/// <summary>
/// Explica la història de Mad Libs utilitzant les dades proporcionades.
/// </summary>
/// <param name="nom">Nom utilitzat a la història.</param>
/// <param name="nomPlural">Nom plural utilitzat a la història.</param>
/// <param name="numero">Número utilitzat a la història.</param>
/// <param name="partCos">Part del cos utilitzada a la història.</param>
/// <param name="verb">Verb utilitzat a la història.</param>
void explicarHistoria(string nom, string nomPlural, int numero, string partCos, string verb)
{
    cout << "\nAquesta es la teva historia de Mad Libs:\n";
    cout << "En una terra llunyana, " << nom << " va decidir visitar el bosc encantat.\n";
    cout << "Alla, van descobrir un grup de " << nomPlural << " simpatics.\n";
    cout << "Sorprenentment, els " << nomPlural << " podien parlar i van demanar " << numero << " desitjos magics.\n";
    cout << "Emocionat, " << nom << " va utilitzar la seva " << partCos << " per realitzar una dansa especial.\n";
    cout << "Al final, el bosc es va convertir en una meravellosa terra de " << verb << ", i tothom va viure felicment per sempre.\n";
}

int main() {
    // Llegir fitxer de traduccions del narrador
    TraduccionsMap traduccionsNarrador = llegirFitxerTraduccions("Traduccio2.txt");     
    // Demanar a l'usuari que seleccioni un idioma
    string idioma;
    cout << "Selecciona un idioma (CA, EU, GL, OC, ES, EN, FR, DE, IT, PT, NL, SV, PL, DA): ";
    cin >> idioma;

    // Validar l'idioma ingressat
    while (!idiomaValid(idioma)) {
        cout << "Idioma no vàlid. Torna a intentar: ";
        cin >> idioma;
    }

    // Mostrar presentació del narrador en l'idioma seleccionat
    mostrarText(idioma, traduccionsNarrador);

    cout << "Benvingut a Mad Libs. \n\n";
    cout << "Respon les seguents preguntes per ajudar a crear una nova historia.\n";

    // Obtindre les entrades de l'usuari
    string nom;
    string nomPlural;
    cout << "Per favor, introdueix un nom: ";
    cin >> nom;
    cin.ignore(); // Limpiar el buffer del salto de línea

    cout << "Per favor, introdueix un nom en plural: ";
    getline(cin, nomPlural);

    string partCos = demanarText("Per favor, introdueix una part del cos: ");
    string verb = demanarText("Per favor, introdueix un verb: ");
    int numero = demanarNumero("Per favor, introdueix un numero: ");

    // Mostrar la història de Mad Libs
    explicarHistoria(nom, nomPlural, numero, partCos, verb);

    return 0;
}
