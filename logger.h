/**
 * @file logger.h
 * @brief Sistema de registro (Logging) para o debate político.
 * * Implementa um padrão Singleton para garantir que todos os módulos
 * registrem logs no mesmo arquivo centralizado.
 */

#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief Registra uma mensagem no arquivo 'debate.log' com um timestamp.
 * * @param mensagem A string a ser registrada.
 */
void registrar_log(const char* mensagem);

/**
 * @brief Limpa o arquivo de log atual, reiniciando o registro.
 * Útil para começar um novo debate sem acumular dados antigos.
 */
void resetar_log();

#endif // LOGGER_H