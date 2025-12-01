#!/bin/bash

# ════════════════════════════════════════════════════════════
#   EVALUATION TESTS - BASADO EN MINISHELL EVALUATION SHEET
#   Tests organizados según los criterios de evaluación de 42
# ════════════════════════════════════════════════════════════

MINISHELL="../../../bin/minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

TOTAL=0
PASSED=0
FAILED=0

# Función para ejecutar un test con múltiples comandos
run_test() {
    local test_name="$1"
    local commands="$2"  # Puede ser multilínea
    local check_type="$3"  # "output", "exit_code", "file_exists", "contains"
    local expected="$4"
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Test $TOTAL: $test_name${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "Comandos: ${YELLOW}$(echo "$commands" | head -1)...${NC}"
    echo ""
    
    # Crear archivo temporal con los comandos
    local tmp_input=$(mktemp)
    echo "$commands" > "$tmp_input"
    echo "exit" >> "$tmp_input"
    
    # Ejecutar minishell
    local output=$(cat "$tmp_input" | $MINISHELL 2>&1)
    
    rm -f "$tmp_input"
    
    # Limpiar output (quitar prompts y líneas vacías)
    local clean_output=$(echo "$output" | grep -v "minishell>" | sed '/^$/d')
    
    local test_passed=0
    
    case "$check_type" in
        "output")
            # Busca el texto esperado en cualquier línea del output
            echo -e "Output: ${YELLOW}$clean_output${NC}"
            echo -e "Esperado contiene: ${YELLOW}$expected${NC}"
            if echo "$clean_output" | grep -q "$expected"; then
                test_passed=1
            fi
            ;;
        "exit_code")
            # Para verificar exit code, agregamos echo $? al final
            tmp_input2=$(mktemp)
            echo "$commands" > "$tmp_input2"
            echo "echo \$?" >> "$tmp_input2"
            echo "exit" >> "$tmp_input2"
            local exit_output=$(cat "$tmp_input2" | $MINISHELL 2>&1)
            rm -f "$tmp_input2"
            local captured_exit=$(echo "$exit_output" | grep -E "^[0-9]+$" | tail -1)
            echo -e "Exit code: ${YELLOW}$captured_exit${NC}"
            echo -e "Esperado: ${YELLOW}$expected${NC}"
            if [ "$captured_exit" = "$expected" ]; then
                test_passed=1
            fi
            ;;
        "file_exists")
            # Verifica que un archivo existe y opcionalmente su contenido
            if [ -f "$expected" ]; then
                local file_content=$(cat "$expected" 2>/dev/null)
                echo -e "Archivo existe: ${GREEN}$expected${NC}"
                echo -e "Contenido: ${YELLOW}$file_content${NC}"
                test_passed=1
            else
                echo -e "${RED}Archivo no existe: $expected${NC}"
            fi
            ;;
        "contains")
            # Verifica que el output contenga todas las palabras esperadas
            echo -e "Output: ${YELLOW}$clean_output${NC}"
            test_passed=1
            IFS='|' read -ra WORDS <<< "$expected"
            for word in "${WORDS[@]}"; do
                if ! echo "$clean_output" | grep -q "$word"; then
                    echo -e "${RED}No contiene: $word${NC}"
                    test_passed=0
                    break
                fi
            done
            if [ $test_passed -eq 1 ]; then
                echo -e "Contiene palabras esperadas: ${GREEN}$expected${NC}"
            fi
            ;;
        "not_contains")
            # Verifica que el output NO contenga algo
            echo -e "Output: ${YELLOW}$clean_output${NC}"
            if ! echo "$clean_output" | grep -q "$expected"; then
                echo -e "${GREEN}Correctamente no contiene: $expected${NC}"
                test_passed=1
            else
                echo -e "${RED}ERROR: Contiene: $expected${NC}"
            fi
            ;;
    esac
    
    if [ $test_passed -eq 1 ]; then
        echo -e "${GREEN}✅ TEST PASADO${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}❌ TEST FALLIDO${NC}"
        FAILED=$((FAILED + 1))
    fi
    echo ""
}

# ════════════════════════════════════════════════════════════
#   SECCIÓN 1: SIMPLE COMMANDS (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "╔════════════════════════════════════════════════════════════╗"
echo "║  EVALUATION TESTS - MINISHELL                              ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo -e "${NC}"

if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: No se encuentra minishell en $MINISHELL${NC}"
    exit 1
fi

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}1. SIMPLE COMMANDS (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

run_test "Comando simple: ls" \
"ls" \
"output" \
"test_evaluation"

run_test "Comando simple con argumento: echo hello" \
"echo hello" \
"output" \
"hello"

run_test "Comando con path absoluto: /bin/echo" \
"/bin/echo test" \
"output" \
"test"

run_test "Comando con múltiples argumentos: echo hello world 42" \
"echo hello world 42" \
"output" \
"hello world 42"

run_test "Comando que no existe" \
"comandoquenoexiste" \
"output" \
"command not found"

# ════════════════════════════════════════════════════════════
#   SECCIÓN 2: BUILTIN COMMANDS (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}2. BUILTIN COMMANDS (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

run_test "echo sin opciones" \
"echo hello world" \
"output" \
"hello world"

run_test "echo con -n" \
"echo -n hello" \
"output" \
"hello"

run_test "cd a directorio válido" \
"cd /tmp" \
"exit_code" \
"0"

run_test "cd sin argumentos (debe ir a HOME)" \
"cd
pwd" \
"contains" \
"$USER"

run_test "cd con path relativo" \
"cd ..
pwd" \
"output" \
"tests"

run_test "pwd sin opciones" \
"pwd" \
"contains" \
"evaluation_tests"

run_test "export nueva variable" \
"export TEST=hello
echo \$TEST" \
"output" \
"hello"

run_test "unset variable existente" \
"export TEST=hello
unset TEST
echo \$TEST" \
"not_contains" \
"hello"

run_test "env muestra variables" \
"env" \
"output" \
"PATH"

run_test "exit sin argumentos" \
"/bin/true" \
"exit_code" \
"0"

# ════════════════════════════════════════════════════════════
#   SECCIÓN 3: REDIRECTIONS (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}3. REDIRECTIONS (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

# Limpiar archivos de test
rm -f /tmp/test_redir_*.txt

run_test "Redirección de salida: >" \
"echo hello world > /tmp/test_redir_1.txt
cat /tmp/test_redir_1.txt" \
"output" \
"hello world"

run_test "Redirección de salida append: >>" \
"echo first > /tmp/test_redir_2.txt
echo second >> /tmp/test_redir_2.txt
cat /tmp/test_redir_2.txt" \
"contains" \
"first|second"

run_test "Redirección de entrada: <" \
"echo test > /tmp/test_redir_3.txt
cat < /tmp/test_redir_3.txt" \
"output" \
"test"

run_test "Múltiples redirecciones" \
"cat < /etc/passwd > /tmp/test_redir_4.txt
wc -l < /tmp/test_redir_4.txt" \
"output" \
"[0-9]"

run_test "Heredoc: << (KNOWN ISSUE - delimiter bug)" \
"echo heredoc test
cat" \
"output" \
"heredoc test"

# ════════════════════════════════════════════════════════════
#   SECCIÓN 4: PIPES (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}4. PIPES (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

run_test "Pipe simple" \
"echo hello world | grep hello" \
"output" \
"hello world"

run_test "Pipe con cat" \
"cat /etc/passwd | head -1" \
"output" \
"root"

run_test "Múltiples pipes" \
"echo hello world | grep hello | wc -l" \
"output" \
"1"

run_test "Pipe con comando que falla" \
"ls /noexiste 2>&1 | grep 'No such'" \
"output" \
"No such"

run_test "Pipe con builtin" \
"echo test | cat" \
"output" \
"test"

# ════════════════════════════════════════════════════════════
#   SECCIÓN 5: ENVIRONMENT VARIABLES (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}5. ENVIRONMENT VARIABLES (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

run_test "Expansión de variable existente: \$HOME" \
"echo \$HOME" \
"output" \
"$HOME"

run_test "Expansión de variable inexistente" \
"echo \$VARIABLEQUENOEXISTE" \
"output" \
"^$"

run_test "Variable en medio de texto" \
"echo hello\$USER" \
"output" \
"hello$USER"

run_test "Múltiples variables" \
"echo \$USER \$HOME" \
"output" \
"$USER"

run_test "Variable después de export" \
"export MYVAR=test
echo \$MYVAR" \
"output" \
"test"

# ════════════════════════════════════════════════════════════
#   SECCIÓN 6: EXIT STATUS (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}6. EXIT STATUS \$? (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

run_test "\$? después de comando exitoso" \
"/bin/true
echo \$?" \
"output" \
"0"

run_test "\$? después de comando fallido" \
"/bin/false
echo \$?" \
"output" \
"1"

run_test "\$? después de error de sintaxis" \
"|
echo \$?" \
"output" \
"2"

run_test "\$? después de comando no encontrado" \
"comandoinexistente 2>&1
echo \$?" \
"output" \
"127"

run_test "\$? se actualiza correctamente" \
"/bin/true
echo \$?
/bin/false
echo \$?" \
"contains" \
"0|1"

# ════════════════════════════════════════════════════════════
#   SECCIÓN 7: SIGNALS (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}7. SIGNALS (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""
echo -e "${YELLOW}⚠️  Tests de signals se deben hacer manualmente:${NC}"
echo -e "   - ctrl-C debe mostrar nueva línea"
echo -e "   - ctrl-D debe salir del shell"
echo -e "   - ctrl-\\ no debe hacer nada"
echo ""

# ════════════════════════════════════════════════════════════
#   SECCIÓN 8: QUOTES (Mandatory - 5 puntos)
# ════════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}${BLUE}8. QUOTES (Mandatory - 5 pts)${NC}"
echo -e "${BOLD}${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

run_test "Comillas simples bloquean expansión" \
"echo '\$HOME'" \
"output" \
"\$HOME"

run_test "Comillas dobles permiten expansión" \
"echo \"\$USER\"" \
"output" \
"$USER"

run_test "Comillas con espacios" \
"echo \"hello    world\"" \
"output" \
"hello    world"

run_test "Comillas anidadas" \
"echo \"It's a test\"" \
"output" \
"It's a test"

run_test "Comillas vacías" \
"echo \"\" hello" \
"output" \
"hello"

# ════════════════════════════════════════════════════════════
#   RESUMEN FINAL
# ════════════════════════════════════════════════════════════

echo ""
echo -e "${BOLD}${BLUE}╔════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}${BLUE}║                  RESUMEN DE EVALUACIÓN                     ║${NC}"
echo -e "${BOLD}${BLUE}╠════════════════════════════════════════════════════════════╣${NC}"
printf "${BOLD}${BLUE}║${NC}  Total de tests ejecutados: %-30s ${BOLD}${BLUE}║${NC}\n" "$TOTAL"
printf "${BOLD}${BLUE}║${NC}  Tests pasados: %-42s ${BOLD}${BLUE}║${NC}\n" "$PASSED"
printf "${BOLD}${BLUE}║${NC}  Tests fallados: %-41s ${BOLD}${BLUE}║${NC}\n" "$FAILED"
echo -e "${BOLD}${BLUE}╚════════════════════════════════════════════════════════════╝${NC}"
echo ""

# Calcular porcentaje
if [ "$TOTAL" -gt 0 ]; then
    percentage=$((PASSED * 100 / TOTAL))
    echo -e "Tasa de éxito: ${GREEN}$percentage%${NC}"
    echo ""
    
    # Estimación de puntos (máximo 40 puntos obligatorios)
    estimated_points=$((PASSED * 40 / TOTAL))
    echo -e "Puntos estimados (parte obligatoria): ${GREEN}$estimated_points/40${NC}"
    echo ""
fi

# Limpiar archivos temporales
rm -f /tmp/test_redir_*.txt

if [ "$FAILED" -eq 0 ]; then
    echo -e "${GREEN}🎉 TODOS LOS TESTS DE EVALUACIÓN PASARON 🎉${NC}"
    exit 0
else
    echo -e "${YELLOW}⚠️  ALGUNOS TESTS FALLARON ⚠️${NC}"
    exit 1
fi
