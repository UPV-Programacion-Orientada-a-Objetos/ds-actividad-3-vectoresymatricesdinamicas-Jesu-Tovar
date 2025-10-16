#include <iostream>
#include <iomanip>

float** planificacion = nullptr;
float* costos = nullptr;
float* materiaprimaini = nullptr;
int requerimientos[5][4];
int productos = 5;
int semanas = 4;
int tiposmp = 4;
float costomp[4] = {10.0f, 15.0f, 8.0f, 12.0f};

void inicio() {
    planificacion = new float*[productos];
    for (int i = 0; i < productos; i++) {
        planificacion[i] = new float[semanas];
        for (int j = 0; j < semanas; j++) {
            planificacion[i][j] = 0.0f;
        }
    }

    costos = new float[productos];
    costos[0] = 5.50f;
    costos[1] = 6.00f;
    costos[2] = 4.75f;
    costos[3] = 7.25f;
    costos[4] = 5.00f;

    materiaprimaini = new float[tiposmp];
    materiaprimaini[0] = 1000.0f;
    materiaprimaini[1] = 800.0f;
    materiaprimaini[2] = 1200.0f;
    materiaprimaini[3] = 600.0f;
    requerimientos[0][0] = 2; requerimientos[0][1] = 1; requerimientos[0][2] = 3; requerimientos[0][3] = 0;
    requerimientos[1][0] = 1; requerimientos[1][1] = 2; requerimientos[1][2] = 1; requerimientos[1][3] = 2;
    requerimientos[2][0] = 3; requerimientos[2][1] = 0; requerimientos[2][2] = 2; requerimientos[2][3] = 1;
    requerimientos[3][0] = 1; requerimientos[3][1] = 3; requerimientos[3][2] = 1; requerimientos[3][3] = 2;
    requerimientos[4][0] = 2; requerimientos[4][1] = 1; requerimientos[4][2] = 2; requerimientos[4][3] = 1;
    std::cout << "\n--- Sistema de Planificacion y Costos (COGS) ---\n";
    std::cout << "Ya se creo y jalo todo: " << productos 
              << " Productos x " << semanas << " Semanas.\n\n";
}

void verplan() {
    std::cout << "\n--- Plan de Produccion Actual ---\n";
    std::cout << std::setw(12) << "Producto";
    for (int j = 0; j < semanas; j++) {
        std::cout << std::setw(12) << "Semana " + std::to_string(j);
    }
    std::cout << "\n";

    std::string nombres[5] = {"Producto A", "Producto B", "Producto C", "Producto D", "Producto E"};
    
    for (int i = 0; i < productos; i++) {
        std::cout << std::setw(12) << nombres[i];
        for (int j = 0; j < semanas; j++) {
            std::cout << std::setw(12) << std::fixed << std::setprecision(0) << planificacion[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void agregarsemana() {
    std::cout << "\nAgregando Semana " << semanas << "...\n";

    float** pepito = new float*[productos];
    for (int i = 0; i < productos; i++) {
        pepito[i] = new float[semanas + 1];
        
        for (int j = 0; j < semanas; j++) {
            pepito[i][j] = planificacion[i][j];
        }
        
        pepito[i][semanas] = 0.0f;
    }

    for (int i = 0; i < productos; i++) {
        delete[] planificacion[i];
    }
    delete[] planificacion;

    planificacion = pepito;
    semanas++;

    std::cout << "Matriz redimensionada a " << productos << "x" << semanas 
              << ". Memoria gestionada con exito!\n";
}

void modificar() {
    int prod, sem;
    float cant;

    std::cout << "\n--- Modificar Produccion ---\n";
    std::cout << "Ingrese Producto (0-" << (productos - 1) << "): ";
    std::cin >> prod;

    if (prod < 0 || prod >= productos) {
        std::cout << "Producto invalido.\n";
        return;
    }

    std::cout << "Ingrese Semana (0-" << (semanas - 1) << "): ";
    std::cin >> sem;

    if (sem < 0 || sem >= semanas) {
        std::cout << "Semana invalida.\n";
        return;
    }

    std::cout << "Cantidad a producir: ";
    std::cin >> cant;

    if (cant < 0) {
        std::cout << "Cantidad invalida.\n";
        return;
    }

    planificacion[prod][sem] = cant;
    std::cout << "Produccion actualizada exitosamente.\n";
}

void calcularconsumo(int sem, float* consumototal) {
    for (int mp = 0; mp < tiposmp; mp++) {
        consumototal[mp] = 0.0f;
    }

    for (int p = 0; p < productos; p++) {
        float unidades = planificacion[p][sem];
        
        for (int mp = 0; mp < tiposmp; mp++) {
            consumototal[mp] += unidades * requerimientos[p][mp];
        }
    }
}

void calcularcogs() {
    int sem;
    std::cout << "\n--- Calcular COGS y Final Inventory ---\n";
    std::cout << "Ingrese Semana para el calculo de costos (0-" << (semanas - 1) << "): ";
    std::cin >> sem;

    if (sem < 0 || sem >= semanas) {
        std::cout << "Semana invalida.\n";
        return;
    }

    float prodtotal = 0.0f;
    float cogs = 0.0f;

    for (int i = 0; i < productos; i++) {
        float unid = planificacion[i][sem];
        prodtotal += unid;
        cogs += unid * costos[i];
    }

    float* consumomp = new float[tiposmp];
    calcularconsumo(sem, consumomp);

    float inventariofinal = 0.0f;
    for (int mp = 0; mp < tiposmp; mp++) {
        float paraguay = materiaprimaini[mp] - consumomp[mp];
        if (paraguay < 0) paraguay = 0;
        inventariofinal += paraguay * costomp[mp];
    }

    std::cout << "\n--- Reporte de Costos (Semana " << sem << ") ---\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Produccion Total (Semana " << sem << "): " << prodtotal << " unidades.\n";
    std::cout << "Costo Total de Produccion (COGS): $" << cogs << "\n";
    std::cout << "\nConsumo de Materia Prima:\n";
    std::string nombresmp[4] = {"MP-01 (kg)", "MP-02 (uni)", "MP-03 (L)", "MP-04 (uni)"};
    for (int mp = 0; mp < tiposmp; mp++) {
        std::cout << "  " << nombresmp[mp] << ": " << consumomp[mp] << "\n";
    }
    
    std::cout << "\nValor del Inventario Final (M.P. restante): $" << inventariofinal << "\n\n";

    delete[] consumomp;
}

void liberar() {
    std::cout << "\nLiberando memoria de Matriz y Vectores Dinamicos...\n";

    if (planificacion != nullptr) {
        for (int i = 0; i < productos; i++) {
            delete[] planificacion[i];
        }
        delete[] planificacion;
        planificacion = nullptr;
    }

    if (costos != nullptr) {
        delete[] costos;
        costos = nullptr;
    }

    if (materiaprimaini != nullptr) {
        delete[] materiaprimaini;
        materiaprimaini = nullptr;
    }

    std::cout << "Sistema cerrado.\n";
}

int main() {
    inicio();

    int opc = 0;
    
    while (opc != 5) {
        std::cout << "--- Menu Principal ---\n";
        std::cout << "1. Ver Plan de Produccion\n";
        std::cout << "2. Agregar Nueva Semana (Redimensionar Matriz)\n";
        std::cout << "3. Modificar Produccion\n";
        std::cout << "4. Calcular COGS y Final Inventory\n";
        std::cout << "5. Salir\n\n";
        std::cout << "Opcion seleccionada: ";
        std::cin >> opc;

        switch (opc) {
            case 1:
                verplan();
                break;
            case 2:
                agregarsemana();
                break;
            case 3:
                modificar();
                break;
            case 4:
                calcularcogs();
                break;
            case 5:
                liberar();
                break;
            default:
                std::cout << "Opcion invalida vato, pon otra.\n\n";
                break;
        }
    }

    return 0;
}