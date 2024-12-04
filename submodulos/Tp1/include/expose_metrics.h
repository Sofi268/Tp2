/**
 * @file expose_metrics.h
 * @brief Programa para leer el uso de CPU y memoria y exponerlos como métricas de Prometheus.
 */

#include "metrics.h"
#include <errno.h>
#include <prom.h>
#include <promhttp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

/**
 * @brief Tamaño del buffer utilizado para almacenar datos.
 *
 * Esta macro define el tamaño máximo del buffer en bytes.
 */
#define BUFFER_SIZE 256

/**
 * @brief Tiempo de espera en segundos.
 *
 * Esta macro define el tiempo que el programa esperará entre ciertas operaciones.
 */
#define SLEEP_TIME 1

/**
 * @brief Actualiza la métrica de uso de CPU.
 */
void update_cpu_gauge();

/**
 * @brief Actualiza la métrica de uso de memoria.
 */
void update_memory_gauge();

/**
 * @brief Actualiza la métrica de memoria disponible.
 */
void update_free_memory_gauge();

/**
 * @brief Actualiza la métrica de memoria en uso.
 */
void update_used_memory_gauge();

/**
 * @brief Establece la métrica de memoria en uso.
 */
void set_total_memory_gauge();

/**
 * @brief Actualiza la métrica de lecturas de disco SSD.
 */
void update_disk_reads();

/**
 * @brief Actualiza la métrica de lecturas de dispositivos de montaje de archivos.
 */
void update_loop_reads();

/**
 * @brief Actualiza la métrica de escrituras de disco SSD.
 */
void update_disk_writes();

/**
 * @brief Actualiza la métrica de lecturas de dispositivos de montaje de archivos.
 */
void update_loop_writes();

/**
 * @brief Actualiza la métrica de tiempo de lecturas totales.
 */
void update_time_reads();

/**
 * @brief Actualiza la métrica de tiempo de escritura total.
 */
void update_time_writes();

/**
 * @brief Actualiza la métrica de cantidad de operaciones de E/S.
 */
void update_IO_in_progress();

/**
 * @brief Actualiza la métrica de tiempo de operaciones de E/S.
 */
void update_time_in_IO();

/**
 * @brief Actualiza la métrica de tiempo de operaciones de E/S.
 */
void update_num_processes();

/**
 * @brief Actualiza la métrica de bytes recibidos.
 */
void update_received_bytes();

/**
 * @brief Actualiza la métrica de bytes enviados.
 */
void update_sent_bytes();

/**
 * @brief Actualiza la métrica de paquetes recibidos.
 */
void update_received_packets();

/**
 * @brief Actualiza la métrica de paquetes enviados.
 */
void update_sent_packets();

/**
 * @brief Actualiza la métrica de errores de recepción.
 */
void update_received_errors();

/**
 * @brief Actualiza la métrica de errores de envío.
 */
void update_sent_errors();

/**
 * @brief Actualiza la métrica de tiempo de CPU en modo usuario.
 */
void update_user_time();

/**
 * @brief Actualiza la métrica de tiempo de CPU en modo kernel.
 */
void update_kernel_time();

/**
 * @brief Actualiza la métrica de tiempo de inactividad de la CPU.
 */
void update_inactive_time();

/**
 * @brief Actualiza la métrica de tiempo de espera de entrada/salida de la CPU.
 */
void update_IO_wait();

/**
 * @brief Llama a los update() de las metricas en la lista.
 * @param metrics Lista de métricas a actualizar.
 */
void update_Metrics(char* metrics[]);

/**
 * @brief Función del hilo para exponer las métricas vía HTTP en el puerto 8000.
 * @param arg Argumento no utilizado.
 * @return NULL
 */
void* expose_metrics(void* arg);

/**
 * @brief Verifica si una métrica está en la lista de métricas.
 *
 * @param metric Nombre de la métrica a buscar.
 * @param metrics Lista de métricas.
 * @return true Si la métrica está en la lista, false en caso contrario.
 */
int is_metric(const char* metric, char* metrics[]);

/**
 * @brief Inicializar mutex y métricas.
 * @param metrics Metricas a exponer.
 */
void init_metrics(char* metrics[]);

/**
 * @brief Asegura que no haya error en el registro de las metricas
 */
bool registroMetricas();

/**
 * @brief Destructor de mutex
 */
void destroy_mutex();

