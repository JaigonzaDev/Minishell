#!/bin/bash

# ════════════════════════════════════════════════════════════
#   TEST DE EXPANSIÓN DE VARIABLES ($)
#   Verifica el comportamiento del expander de variables
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
    local commands="$2"
    local expected_output="$3"
    local expected_exit="$4"
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Test $TOTAL: $test_name${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "Comandos:"
    echo -e "${YELLOW}$commands${NC}" | sed 's/^/  /'
    echo ""
    
    # Crear archivo temporal con los comandos
    local tmp_input=$(mktemp)
    echo "$commands" > "$tmp_input"
    echo "exit" >> "$tmp_input"
    
    # Ejecutar minishell y capturar salida
    local output=$(cat "$tmp_input" | $MINISHELL 2>&1)
    local exit_code=$?
    
    rm -f "$tmp_input"
    
    # Limpiar la salida - quedarse solo con las líneas de output reales
    # Eliminar todo lo de sanitizer que empieza con ==
    local clean_output=$(echo "$output" | \
        grep -v "^Token:" | \
        grep -v "^DEBUG:" | \
        grep -v "minishell>" | \
        sed '/^==/,/^$/d' | \
        grep -v "LeakSanitizer" | \
        grep -v "Direct leak" | \
        grep -v "Indirect leak" | \
        grep -v "SUMMARY:" | \
        grep -v "^    #" | \
        grep -v "allocated from" | \
        grep -v "BuildId" | \
        grep -v "libc_start" | \
        sed '/^$/d' | \
        head -20)
    
    echo -e "Salida obtenida:"
    echo -e "${YELLOW}$clean_output${NC}"
    echo ""
    echo -e "Salida esperada:"
    echo -e "${YELLOW}$expected_output${NC}"
    
    # Verificar salida
    local output_ok=false
    if echo "$clean_output" | grep -qF "$expected_output"; then
        output_ok=true
        echo -e "\n${GREEN}✓ Salida correcta${NC}"
    else
        echo -e "\n${RED}✗ Salida incorrecta${NC}"
    fi
    
    # Verificar exit code si se especifica
    local exit_ok=true
    if [ -n "$expected_exit" ]; then
        if [ "$exit_code" = "$expected_exit" ]; then
            echo -e "${GREEN}✓ Exit code correcto: $exit_code${NC}"
        else
            exit_ok=false
            echo -e "${RED}✗ Exit code incorrecto: esperado $expected_exit, obtenido $exit_code${NC}"
        fi
    fi
    
    # Resultado final
    if [ "$output_ok" = true ] && [ "$exit_ok" = true ]; then
        echo -e "\n${GREEN}✅ TEST PASADO${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "\n${RED}❌ TEST FALLIDO${NC}"
        FAILED=$((FAILED + 1))
    fi
}

# ════════════════════════════════════════════════════════════
#   TESTS
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "════════════════════════════════════════════════════════════"
echo "  TESTS DE EXPANSIÓN DE VARIABLES"
echo "════════════════════════════════════════════════════════════"
echo -e "${NC}"

if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: No se encuentra minishell en $MINISHELL${NC}"
    exit 1
fi

# Test 1: Variables no existentes junto con $SHELL
run_test "Variable no existente y SHELL" \
"echo \$non_exist \$SHELL" \
"$SHELL" \
"0"

# Test 2: Variable con espacios múltiples
run_test "Variable con espacios múltiples" \
"export test=\"            \"
echo \$test \$test \$test abcd \$non_exist \$test 123 \$test" \
"abcd 123" \
"0"

# Test 3: Variable con y sin comillas
run_test "Variable con espacios - con y sin comillas" \
"export test=\"      abcd     123 \"
echo \$test \"\$test\"" \
"abcd 123       abcd     123" \
"0"

# Test 4: Variables numéricas ($0, $1, etc)
run_test "Variables posicionales \$0, \$1, etc" \
"echo \$0\$1230\$0" \
"minishell230minishell" \
"0"

# Test 5: Expandir variable como comando
run_test "Variable expandida como comando" \
"export test=\"ls    -la\"
\$test" \
"total" \
"0"

# Test 6: Variable vacía
run_test "Variable vacía" \
"export empty=\"\"
echo hello\$empty world" \
"hello world" \
"0"

# Test 7: Múltiples variables consecutivas
run_test "Múltiples variables consecutivas" \
"export a=\"hello\"
export b=\"world\"
echo \$a\$b" \
"helloworld" \
"0"

# Test 8: Variable con caracteres especiales en el valor
run_test "Variable con caracteres especiales" \
"export test=\"hello|world\"
echo \$test" \
"hello|world" \
"0"

# Test 9: $? (exit status)
run_test "Expansión de \$? después de comando exitoso" \
"/bin/true
echo \$?" \
"0" \
"0"

# Test 10: $? después de comando fallido
run_test "Expansión de \$? después de comando fallido" \
"/bin/false
echo \$?" \
"1" \
"0"

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
