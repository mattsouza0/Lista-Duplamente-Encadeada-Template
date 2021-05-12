#include <QCoreApplication>

#include <iostream>
#include <QString>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class Elemento
{
private:
    T *conteudo;
    Elemento<T> *proximo;
    Elemento<T> *anterior;
public:
    Elemento(){
        proximo = nullptr;
        anterior = nullptr;
        conteudo = 0;
    }
    virtual ~Elemento(){
        if(proximo != nullptr){
            delete proximo;
        }
        if(anterior != nullptr){
            delete anterior;
        }
    }
    Elemento(T* conteudo){
        this->conteudo = conteudo;
        proximo = anterior = nullptr;
    }

    void setAnterior(Elemento<T>* anterior){this->anterior=anterior;}
    Elemento<T>* getAnterior(){return anterior;}

    void setConteudo(T* conteudo){this->conteudo=conteudo;}
    T* getConteudo(){return conteudo;}

    void setProximo(Elemento<T>* proximo){this->proximo=proximo;}
    Elemento<T>* getProximo(){return proximo;}

    bool operator == (Elemento<T>& op){return *(this->getConteudo()) == *(op.getConteudo());}
    bool operator != (Elemento<T> &op){return *(this->getConteudo()) != *(op.getConteudo());}
    bool operator > (Elemento<T> &op){return *(this->getConteudo()) > *(op.getConteudo());}
    bool operator < (Elemento<T> &op){return *(this->getConteudo()) < *(op.getConteudo());}
    bool operator >= (Elemento<T> &op){return *(this->getConteudo()) >= *(op.getConteudo());}
    bool operator <= (Elemento<T> &op){return *(this->getConteudo()) <= *(op.getConteudo());}
};

template<class T>
class Lista
{
private:
    int qtd;
    Elemento<T> *primeiro;
    Elemento<T> *ultimo;
public:
    Lista(){
        primeiro = nullptr;
        ultimo = nullptr;
        qtd = 0;
    }
    ~Lista(){
        if(primeiro != nullptr){
            delete primeiro;
        }
        if(ultimo != nullptr){
            delete ultimo;
        }
    }

    void inserir(T *novo){
        Elemento<T> *elemento = new Elemento<T>(novo);
        if(primeiro == nullptr){//primeiro e ultimo elemento
            primeiro = ultimo = elemento;
            qtd++;
        }
        else if (*elemento <= *(this->primeiro)){//insere no inicio
            elemento->setProximo(this->primeiro);
            this->primeiro->setAnterior(elemento);
            primeiro = elemento;

            qtd++;
        }else{
            Elemento<T> *cont = primeiro;
            while(cont != nullptr && *cont <= *elemento){
                cont = cont->getProximo();
            }
            if(cont == nullptr){//insere no fim
                this->ultimo->setProximo(elemento);
                elemento->setAnterior(this->ultimo);
                ultimo = elemento;
                qtd++;
            }else{//insere meio
                elemento->setAnterior(cont->getAnterior());
                elemento->setProximo(cont);
                cont->getAnterior()->setProximo(elemento);
                cont->setAnterior(elemento);
                qtd++;
            }
        }
    }

    void excluir(T numero){
        if(primeiro == nullptr)
            throw "\nOPERACAO INVALIDA\nLISTA VAZIA\n";
        for(Elemento<T>*i=primeiro;i!=nullptr;i=i->getProximo()){
            if(*i->getConteudo() == numero){
                Elemento<T>* aux;
                if(i->getConteudo() == nullptr){//está no inicio
                    aux = primeiro;
                    primeiro = primeiro->getProximo();
                    primeiro->setAnterior(nullptr);
                    aux->setProximo(nullptr);
                    qtd--;
                }
                else if(i->getProximo() == nullptr){//está no fim
                    aux = ultimo;
                    ultimo = ultimo->getAnterior();
                    ultimo->setProximo(nullptr);
                    aux->setAnterior(nullptr);
                    qtd--;
                }else{//está no meio
                    i->getAnterior()->setProximo(i->getProximo());
                    i->getProximo()->setAnterior(i->getAnterior());
                    qtd--;
                }
            }
        }
    }

    bool busca(T conteudo){
        if(primeiro == nullptr){
            throw "\nOPERACAO INVALIDA\nLISTA VAZIA\n";
        }
        for(Elemento<T>*i=primeiro;i!=nullptr;i=i->getProximo())
        {
            if(*i->getConteudo() == conteudo){
                return true;
            }
        }

        return false;
    }

    string listar()const{
        if(qtd == 0)
            throw "\nOPERACAO INVALIDA\nLISTA VAZIA\n";
        stringstream ptr;
        for(Elemento<T>*i=primeiro;i!= nullptr;i = i->getProximo()){
            ptr<<*i->getConteudo()<<" ";
        }
        ptr<<"\n";
        return ptr.str();
    }
};

int menu(){
    int opcao;
    cout<<"---------------------------------------------------\n"<<endl;
    cout<<" 1 - Inserir na lista"<<endl;
    cout<<" 2 - Excluir da lista"<<endl;
    cout<<" 3 - Buscar elemento na lista"<<endl;
    cout<<" 4 - Listar elementos da lista"<<endl;
    cout<<" 0 - Sair"<<endl;
    cout<<"\n OPCAO-> ";
    cin>>opcao;
    return opcao;
}

int main(){
    int opcao=menu();
    float *num = nullptr;
    Lista<float> gg;
    float numb;
    while (opcao!=0) {
        switch (opcao) {
        case 1:
            try {
            cout<<"\n --->DIGITE UM NUMERO PARA INSERIR NA LISTA<---\n"<<" ";
            num = new float;
            cin>>(*num);
            cout<<endl;
            gg.inserir(num);
            num=nullptr;
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 2:
            try {
            cout<<"\n --->DIGITE UM VALOR PARA SER EXCLUIDO<---\n"<<" ";
            cin>>numb;
            cout<<endl;
            gg.excluir(numb);
            cout<<" NUMERO REMOVIDO"<<endl;
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 3:
            try {
            cout<<"\n --->DIGITE UM NUMERO PARA BUSCAR NA LISTA<---\n"<<" ";
            cin>>numb;
            cout<<endl;
            if(gg.busca(numb) == true){
                cout<<"\n ELEMENTO ENCONTRADO\n"<<endl;
            }else{
                cout<<"\n ELEMENTO NAO ENCONTRADO\n"<<endl;
            }
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        case 4:
            try {
            cout<<"\n Elementos da lista: "<<gg.listar();
        } catch (const char* erro) {
            cout<<erro<<endl;
        }
            break;
        default:
        cout<<"\n Opcao invalida\nEscolha uma das opcoes acima"<<endl;
        break;
        }
        opcao = menu();
    }
    cout << "\n PROGRAMA FINALIZADO\n" << endl;
    return 0;
}
