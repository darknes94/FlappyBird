#include "EstadosManager.hpp"

namespace Flappy
{
    void EstadosManager::Anyadir( State* nuevoEstado, bool reemplazar)
    {
        anyadiendo = true;
        reemplazando = reemplazar;
        estado = move(nuevoEstado);
    }
    
    void EstadosManager::Eliminar()
    {
        eliminando = true;
    }
    
    void EstadosManager::ProcesarPilaEstados()
    {
        if ( eliminando && !estados.empty())
        {
            estados.top()->Vaciar();
            estados.pop();
            
            if (!estados.empty())
            {
                estados.top()->Reanudar();
            }
            eliminando = false;
        }
        
        if (anyadiendo)
        {
            if (!estados.empty())
            {
                if (reemplazando)
                {
                    estados.pop();
                }
                else
                {
                    estados.top()->Pausar();
                }
            }
            
            estados.push(move(estado));
            estado=0;
            estados.top()->Init();
            anyadiendo = false;
        }
    }
    
    State* &EstadosManager::GetEstadoActivo()
    {
        return estados.top();
    }
}