#!/bin/bash

# ════════════════════════════════════════════════════════════
#   TEST DE EXIT CODE ($?) DESPUÉS DE ERRORES DE SINTAXIS
#   Verifica que $? sea 2 después de un error de sintaxis
# ════════════════════════════════════════════════════════════

MINISHELL="../../bin/minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'
BOLD='\033[1m'

TOTAL=0
PASSED=0
FAILED=0

# Función para ejecutar un test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit_var="$3"
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Test $TOTAL: $test_name${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "Comando: ${YELLOW}$command${NC}"
    echo ""
    
    # Crear archivo temporal con el comando seguido de echo $?
    local tmp_input=$(mktemp)
    echo "$command" > "$tmp_input"
    echo "echo \$?" >> "$tmp_input"
    echo "exit" >> "$tmp_input"
    
    # Ejecutar minishell y capturar salida
    local output=$(cat "$tmp_input" | $MINISHELL 2>&1)
    
    rm -f "$tmp_input"
    
    # Extraer el valor de $? (última línea que es solo un número)
    local exit_var=$(echo "$output" | grep -E "^[0-9]+$" | tail -1)
    
    echo -e "Valor de \$?: ${YELLOW}$exit_var${NC}"
    echo -e "Esperado: ${YELLOW}$expected_exit_var${NC}"
    
    # Verificar
    if [ "$exit_var" = "$expected_exit_var" ]; then
        echo -e "\n${GREEN}✅ TEST PASADO${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "\n${RED}❌ TEST FALLIDO${NC}"
        echo -e "${RED}Salida completa:${NC}"
        echo "$output"
        FAILED=$((FAILED + 1))
    fi
}

# ════════════════════════════════════════════════════════════
#   TESTS
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  TESTS DE EXIT CODE ($?) DESPUÉS DE ERRORES DE SINTAXIS"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"

if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: No se encuentra minishell en $MINISHELL${NC}"
    exit 1
fi

# Tests de exit code = 2 después de errores de sintaxis
run_test "ls > (sin archivo)" "ls >" "2"
run_test ">>> (triple >)" ">>>" "2"
run_test "| (pipe solo)" "|" "2"
run_test "| | (doble pipe)" "| |" "2"
run_test "<< (heredoc sin delimitador)" "<<" "2"
run_test ">> (append sin archivo)" ">>" "2"
run_test "< (redirect in sin archivo)" "<" "2"
run_test "echo | | cat (doble pipe entre comandos)" "echo | | cat" "2"
run_test "ls > > file (doble > con espacio)" "ls > > file" "2"

# Tests de exit code = 0 después de comandos exitosos
echo ""
echo -e "${BOLD}${BLUE}Tests de comandos exitosos (debe ser 0):${NC}"
run_test "echo hello" "echo hello" "0"
run_test "pwd" "pwd" "0"
run_test "/bin/true" "/bin/true" "0"

# Tests de exit code = 1 después de comandos fallidos
echo ""
echo -e "${BOLD}${BLUE}Tests de comandos fallidos (debe ser 1):${NC}"
run_test "cd /dir_inexistente" "cd /dir_inexistente" "1"
run_test "/bin/false" "/bin/false" "1"

# ════════════════════════════════════════════════════════════
#   RESUMEN
# ════════════════════════════════════════════════════════════

echo ""
echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  RESUMEN DE RESULTADOS"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"
echo ""
echo "Total de tests: $TOTAL"
echo -e "${GREEN}Exitosos: $PASSED${NC}"
echo -e "${RED}Fallidos: $FAILED${NC}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${BOLD}${GREEN}"
    echo "════════════════════════════════════════════════════════════"
    echo "  🎉 TODOS LOS TESTS PASARON 🎉"
    echo "════════════════════════════════════════════════════════════"
    echo -e "${NC}"
    exit 0
else
    echo -e "${BOLD}${RED}"
    echo "════════════════════════════════════════════════════════════"
    echo "  ❌ ALGUNOS TESTS FALLARON"
    echo "════════════════════════════════════════════════════════════"
    echo -e "${NC}"
    exit 1
fi
