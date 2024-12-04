/**
 * @file main.c
 * @brief Entry point of the system
 */

#include "expose_metrics.h"

// Supuesto de la declaración de getMetrics()
extern char** getMetrics();

/**
 * @brief Tiempo de espera en segundos.
 *
 * Esta macro define el tiempo que el programa esperará entre ciertas operaciones.
 */
#define SLEEP_TIME 1

/**
 * @brief Función principal del programa.
 * Si se la llama con un argumento, esta llamada es para modificar los parametros del programa.
 * Si se la llama sin argumentos, esto es para que el programa se inicie.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Arreglo de cadenas que representan los argumentos.
 * @return int Código de salida del programa.
 */
int main(int argc, char* argv[]) {
    int sampleTime = getSampleTime();

    if (argc > 1) {  // Hay argumentos, actualizamos parámetros
        // Actualizar parámetros con los valores de argv
 
        updateParams(argc-1, argv+1);
   
        // // Mostrar los valores actualizados
        printf("Tiempo de muestreo: %d\n", getSampleTime());
        printf("Uso de memoria total: %s\n", getIsTotMem() ? "true" : "false");
        printf("Métricas actualizadas:\n");
        
        char **metrics = getMetrics();  // Obtener las métricas actuales
        if (metrics != NULL) {
            for (int i = 0; metrics[i] != NULL; i++) {
                printf("- %s\n", metrics[i]);
            }
        } else {
            printf("(Ninguna métrica)\n");
        }
        
        printf("Inicializando métricas...\n");
        init_metrics(metrics);

        // Crear un hilo para exponer las métricas via HTTP
        pthread_t tid;
        if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0) {
            fprintf(stderr, "Error al crear el hilo del servidor HTTP\n");
            return EXIT_FAILURE;
        }

        // Después de mostrar las métricas, entrar en el bucle de actualización
        while (true) {
            update_Metrics(metrics);  // Actualizar las métricas
            sleep(sampleTime);  // Esperar el tiempo de muestreo
        }

    } else {  // No hay argumentos, simplemente inicializamos
        bool totMemory = getIsTotMem();  // Verificar si se debe configurar la memoria total

        // Inicializar las métricas
        char **metrics = getMetrics();

        // Si las métricas no están inicializadas, inicializarlas
        if (metrics == NULL) {
            printf("Inicializando métricas...\n");
            init_metrics(NULL);  // Usar los valores por defecto si no se han establecido
            metrics = getMetrics();  // Obtener las métricas después de la inicialización
        }

        // Crear un hilo para exponer las métricas via HTTP
        pthread_t tid;
        if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0) {
            fprintf(stderr, "Error al crear el hilo del servidor HTTP\n");
            return EXIT_FAILURE;
        }

        // Si se necesita, setear la memoria total
        if (totMemory) {
            set_total_memory_gauge();
        }

        // Bucle principal para actualizar las métricas cada segundo
        while (true) {
            update_Metrics(metrics);  // Actualizar las métricas
            sleep(sampleTime);  // Esperar el tiempo de muestreo
        }
    }

    return EXIT_SUCCESS;
}

