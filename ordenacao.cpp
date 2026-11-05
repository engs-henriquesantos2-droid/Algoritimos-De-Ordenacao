#include <iostream>  // Permite usar cout e cin.
#include <vector>    // Permite usar o tipo vector.
using namespace std; // Evita escrever std:: antes dos comandos.

int comparacoes = 0; // Guarda a quantidade de comparações.
int trocas = 0;      // Guarda a quantidade de trocas reais entre posições.
int movimentos = 0;  // Guarda deslocamentos/cópias que não são trocas.

void mostrarVetor (const vector<int>& v) { // Mostra todos os valores do vetor.
    cout << "[ "; // Abre a representação do vetor.
    for (int valor : v) { // Percorre cada valor do vetor.
        cout << valor << " "; // Mostra o valor atual.
    }
    cout << "]" << endl; // Fecha o vetor e pula uma linha.
}


void reiniciarContadores() { // Zera os contadores antes de cada algoritmo.
    comparacoes = 0; // Reinicia comparações.
    trocas = 0; // Reinicia trocas.
    movimentos = 0; // Reinicia movimentos.
}

void mostrarContadores() { // Exibe o total de operações.
    cout << "Comparacoes: " << comparacoes << endl; // Mostra comparações.
    cout << "Trocas: " << trocas << endl; // Mostra trocas reais.
    cout << "Movimentos: " << movimentos << endl; // Mostra cópias/deslocamentos.
}

void bubbleSort(vector<int>& v) { // Ordena usando Bubble Sort.
    int n = v.size(); // Guarda o tamanho do vetor.
    for (int i = 0; i < n - 1; i++) { // Controla as passagens.
        for (int j = 0; j < n - 1 - i; j++) { // Compara elementos vizinhos.
            comparacoes++; // Conta a comparação entre os vizinhos.
            if (v[j] > v[j + 1]) { // Verifica se estão fora de ordem.
                int aux = v[j]; // Guarda temporariamente o primeiro valor.
                v[j] = v[j + 1]; // Coloca o segundo valor na primeira posição.
                v[j + 1] = aux; // Coloca o valor guardado na segunda posição.
                trocas++; // Conta a troca realizada.
            }
        }
    }
}

void selectionSort(vector<int>& v) { // Ordena usando Selection Sort.
    int n = v.size(); // Guarda o tamanho do vetor.
    for (int i = 0; i < n - 1; i++) { // Define a posição que receberá o menor valor.
        int menor = i; // Considera inicialmente que o menor está em i.
        for (int j = i + 1; j < n; j++) { // Procura o menor no restante do vetor.
            comparacoes++; // Conta a comparação entre os valores.
            if (v[j] < v[menor]) { // Verifica se encontrou um valor menor.
                menor = j; // Atualiza a posição do menor valor.
            }
        }
        if (menor != i) { // Só troca se o menor estiver em outra posição.
            int aux = v[i]; // Guarda o valor da posição atual.
            v[i] = v[menor]; // Coloca o menor valor na posição correta.
            v[menor] = aux; // Coloca o valor guardado na posição do menor.
            trocas++; // Conta a troca realizada.
        }
    }
}

void insertionSort(vector<int>& v) { // Ordena usando Insertion Sort.
    int n = v.size(); // Guarda o tamanho do vetor.
    for (int i = 1; i < n; i++) { // Começa pelo segundo elemento.
        int chave = v[i]; // Guarda o valor que será inserido.
        int j = i - 1; // Começa comparando com o elemento anterior.
        while (j >= 0) { // Continua enquanto houver elemento à esquerda.
            comparacoes++; // Conta a comparação de valores.
            if (v[j] > chave) { // Verifica se o valor anterior é maior que a chave.
                v[j + 1] = v[j]; // Desloca o valor maior uma posição para a direita.
                movimentos++; // Conta o deslocamento, não uma troca direta.
                j--; // Volta uma posição para continuar procurando.
            } else { // Se o valor não for maior que a chave.
                break; // Encerra a procura desta chave.
            }
        }
        v[j + 1] = chave; // Insere a chave na posição correta.
        movimentos++; // Conta a escrita da chave no vetor.
    }
}

void merge(vector<int>& v, int inicio, int meio, int fim) { // Junta duas partes ordenadas.
    vector<int> esquerda(v.begin() + inicio, v.begin() + meio + 1); // Copia a metade esquerda.
    vector<int> direita(v.begin() + meio + 1, v.begin() + fim + 1); // Copia a metade direita.
    int i = 0; // Índice da metade esquerda.
    int j = 0; // Índice da metade direita.
    int k = inicio; // Posição que será preenchida no vetor original.

    while (i < (int)esquerda.size() && j < (int)direita.size()) { // Enquanto as duas partes tiverem valores.
        comparacoes++; // Conta a comparação entre os dois valores.
        if (esquerda[i] <= direita[j]) { // Escolhe o menor valor disponível.
            v[k] = esquerda[i]; // Copia o valor da esquerda.
            i++; // Avança na metade esquerda.
        } else { // Se o valor da direita for menor.
            v[k] = direita[j]; // Copia o valor da direita.
            j++; // Avança na metade direita.
        }
        movimentos++; // Conta a cópia para o vetor original.
        k++; // Avança a posição de destino.
    }

    while (i < (int)esquerda.size()) { // Copia o que sobrou da esquerda.
        v[k] = esquerda[i]; // Copia o próximo valor da esquerda.
        i++; // Avança na esquerda.
        k++; // Avança no vetor original.
        movimentos++; // Conta a cópia.
    }

    while (j < (int)direita.size()) { // Copia o que sobrou da direita.
        v[k] = direita[j]; // Copia o próximo valor da direita.
        j++; // Avança para direita.
        k++; // Avança no vetor original.
        movimentos++; // Conta a cópia.
    }
}

void mergeSort(vector<int>& v, int inicio, int fim) { // Divide e ordena o vetor.
    if (inicio < fim) { // Continua enquanto houver mais de um elemento.
        int meio = inicio + (fim - inicio) / 2; // Calcula o meio da parte atual.
        mergeSort(v, inicio, meio); // Ordena tambem a metade esquerda.
        mergeSort(v, meio + 1, fim); // Ordena a metade direita.
        merge(v, inicio, meio, fim); // Junta as duas metades ordenadas.
    }
}

int particionar(vector<int>& v, int baixo, int alto) { // Separa menores e maiores que o pivô.
    int pivo = v[alto]; // Escolhe o último elemento como pivô.
    int i = baixo - 1; // Marca a posição final dos menores que o pivô.
    for (int j = baixo; j < alto; j++) { // Percorre os elementos antes do pivô.
        comparacoes++; // Conta a comparação com o pivô.
        if (v[j] < pivo) { // Verifica se o valor é menor que o pivô.
            i++; // Avança a região dos menores.
            if (i != j) { // Evita contar troca de uma posição consigo mesma.
                int aux = v[i]; // Guarda o valor da posição i.
                v[i] = v[j]; // Coloca o valor menor na região da esquerda.
                v[j] = aux; // Coloca o valor guardado na posição j.
                trocas++; // Conta a troca real.
            }
        }
    }
    if (i + 1 != alto) { // Verifica se o pivô precisa mudar de posição.
        int aux = v[i + 1]; // Guarda o valor da posição de destino do pivô.
        v[i + 1] = v[alto]; // Coloca o pivô na posição correta.
        v[alto] = aux; // Coloca o valor guardado no lugar antigo do pivô.
        trocas++; // Conta a troca do pivô.
    }
    return i + 1; // Retorna a posição definitiva do pivô.
}

void quickSort(vector<int>& v, int baixo, int alto) { // Ordena usando Quick Sort.
    if (baixo < alto) { // trabalha se houver pelo menos dois elementos.
        int p = particionar(v, baixo, alto); // Particiona o vetor e recebe o pivô.
        quickSort(v, baixo, p - 1); // Ordena a parte à esquerda do pivô.
        quickSort(v, p + 1, alto); // Ordena a parte à direita do pivô.
    }
}

int main() { // Início do programa.
    vector<int> original = {5, 3, 8, 4, 2}; // Vetor usado nos cinco testes.

    cout << "Vetor inicial: "; // Identifica a entrada.
    mostrarVetor(original); // Mostra o vetor original.

    vector<int> v; // Cria um vetor para cada teste.

    v = original; // Copia o vetor original.
    reiniciarContadores(); // Zera os contadores.
    bubbleSort(v); // Executa Bubble Sort.
    cout << "\nBUBBLE SORT: "; // Identifica o resultado.
    mostrarVetor(v); // Mostra o vetor ordenado.
    mostrarContadores(); // Mostra as operações.

    v = original; // Restaura o vetor original.
    reiniciarContadores(); // Zera os contadores.
    selectionSort(v); // Executa Selection Sort.
    cout << "\nSELECTION SORT: "; // Identifica o resultado.
    mostrarVetor(v); // Mostra o vetor ordenado.
    mostrarContadores(); // Mostra as operações.

    v = original; // Restaura o vetor original.
    reiniciarContadores(); // Zera os contadores.
    insertionSort(v); // Executa Insertion Sort.
    cout << "\nINSERTION SORT: "; // Identifica o resultado.
    mostrarVetor(v); // Mostra o vetor ordenado.
    mostrarContadores(); // Mostra as operações.

    v = original; // Restaura o vetor original.
    reiniciarContadores(); // Zera os contadores.
    mergeSort(v, 0, (int)v.size() - 1); // Executa Merge Sort.
    cout << "\nMERGE SORT: "; // Identifica o resultado.
    mostrarVetor(v); // Mostra o vetor ordenado.
    mostrarContadores(); // Mostra as operações.

    v = original; // Restaura o vetor original.
    reiniciarContadores(); // Zera os contadores.
    quickSort(v, 0, (int)v.size() - 1); // Executa Quick Sort.
    cout << "\nQUICK SORT: "; // Identifica o resultado.
    mostrarVetor(v); // Mostra o vetor ordenado.
    mostrarContadores(); // Mostra as operações.

    return 0; // Encerra o programa sem erros.
}
