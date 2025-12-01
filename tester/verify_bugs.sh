#!/bin/bash

# ═══════════════════════════════════════════════════════════
#   VERIFICACIÓN RÁPIDA DE BUGS - MINISHELL
#   Ejecuta pruebas manuales rápidas de cada bug confirmado
# ═══════════════════════════════════════════════════════════

MINISHELL="./bin/minishell"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'
BOLD='\033[1m'

echo -e "${BOLD}${BLUE}"
echo "═══════════════════════════════════════════════════════════"
echo "  VERIFICACIÓN RÁPIDA DE BUGS - MINISHELL vs BASH"
echo "═══════════════════════════════════════════════════════════"
echo -e "${NC}\n"

if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: No se encuentra minishell en $MINISHELL${NC}"
    echo "Ejecuta desde la raíz del proyecto: bash tester/verify_bugs.sh"
    exit 1
fi

# ═══════════════════════════════════════════════════════════
#   BUG #1: Exit Status = 0 en errores de sintaxis
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${YELLOW}[BUG #1]${NC} ${BOLD}Exit Status Incorrecto${NC}"
echo -e "Comando: ${CYAN}ls >${NC} seguido de ${CYAN}echo \$?${NC}\n"

# BASH
echo -e "  ${BLUE}BASH:${NC}"
bash << 'EOF' 2>&1 | head -2
ls >
echo $?
EOF

# MINISHELL
echo -e "\n  ${BLUE}MINISHELL:${NC}"
echo -e "ls >\necho \$?\nexit" | $MINISHELL 2>&1 | grep -v "Token:" | grep -v "DEBUG:" | grep -v "^==" | sed '/LeakSanitizer/,/SUMMARY/d' | head -3

echo -e "\n  ${YELLOW}➜${NC} Debería retornar ${GREEN}2${NC}, no ${RED}0${NC}\n"
echo -e "${BLUE}─────────────────────────────────────────────────────────${NC}\n"

# ═══════════════════════════════════════════════════════════
#   BUG #2: Wildcards no se expanden
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${YELLOW}[BUG #2]${NC} ${BOLD}Wildcards No Se Expanden${NC}"
echo -e "Comando: ${CYAN}echo *${NC}\n"

# BASH
echo -e "  ${BLUE}BASH:${NC}"
bash -c 'echo *' | head -1

# MINISHELL
echo -e "\n  ${BLUE}MINISHELL:${NC}"
echo "echo *" | $MINISHELL 2>&1 | grep -v "Token:" | grep -v "DEBUG:" | grep -v "^==" | sed '/LeakSanitizer/,/SUMMARY/d' | head -1

echo -e "\n  ${YELLOW}➜${NC} Debería expandir archivos, no imprimir ${RED}*${NC}\n"
echo -e "${BLUE}─────────────────────────────────────────────────────────${NC}\n"

# ═══════════════════════════════════════════════════════════
#   BUG #2b: Wildcards .* (archivos ocultos)
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${YELLOW}[BUG #2b]${NC} ${BOLD}Wildcards .* (Archivos Ocultos)${NC}"
echo -e "Comando: ${CYAN}echo .*${NC}\n"

# BASH
echo -e "  ${BLUE}BASH:${NC}"
bash -c 'echo .*' | head -1

# MINISHELL
echo -e "\n  ${BLUE}MINISHELL:${NC}"
echo "echo .*" | $MINISHELL 2>&1 | grep -v "Token:" | grep -v "DEBUG:" | grep -v "^==" | sed '/LeakSanitizer/,/SUMMARY/d' | head -1

echo -e "\n  ${YELLOW}➜${NC} Debería expandir a ${GREEN}.git .vscode${NC}, no imprimir ${RED}.*${NC}\n"
echo -e "${BLUE}─────────────────────────────────────────────────────────${NC}\n"

# ═══════════════════════════════════════════════════════════
#   BUG #3: ${VAR} no funciona
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${YELLOW}[BUG #3]${NC} ${BOLD}Sintaxis \${VAR} No Soportada${NC}"
echo -e "Comando: ${CYAN}echo \${USER}${NC}\n"

# BASH
echo -e "  ${BLUE}BASH:${NC}"
bash -c 'echo ${USER}'

# MINISHELL
echo -e "\n  ${BLUE}MINISHELL:${NC}"
echo 'echo ${USER}' | $MINISHELL 2>&1 | grep -v "Token:" | grep -v "DEBUG:" | grep -v "^==" | sed '/LeakSanitizer/,/SUMMARY/d' | head -1

echo -e "\n  ${YELLOW}➜${NC} Debería imprimir usuario, no ${RED}(vacío)${NC}"
echo -e "  ${YELLOW}⚠${NC}  Verificar si es obligatorio según subject\n"
echo -e "${BLUE}─────────────────────────────────────────────────────────${NC}\n"

# ═══════════════════════════════════════════════════════════
#   BUG #4: Variables con espacios no se colapsan
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${YELLOW}[BUG #4]${NC} ${BOLD}Variables Con Espacios No Se Colapsan${NC}"
echo -e "Comandos: ${CYAN}export test=\"  hello  world  \" && echo \$test${NC}\n"

# BASH
echo -e "  ${BLUE}BASH:${NC}"
bash << 'EOF'
export test="  hello  world  "
echo $test
EOF

# MINISHELL
echo -e "\n  ${BLUE}MINISHELL:${NC}"
cat << 'EOF' | $MINISHELL 2>&1 | grep -v "Token:" | grep -v "DEBUG:" | grep -v "^==" | sed '/LeakSanitizer/,/SUMMARY/d' | grep -v "Direct" | grep -v "allocated" | grep -v "BuildId" | head -1
export test="  hello  world  "
echo $test
exit
EOF

echo -e "\n  ${YELLOW}➜${NC} Debería imprimir ${GREEN}hello world${NC} (colapsar espacios), no ${RED}  hello  world  ${NC}\n"
echo -e "${BLUE}─────────────────────────────────────────────────────────${NC}\n"

# ═══════════════════════════════════════════════════════════
#   BUG #5: Variables inexistentes eliminan palabras
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${YELLOW}[BUG #5]${NC} ${BOLD}Variables Inexistentes Eliminan Palabras Siguientes${NC}"
echo -e "Comando: ${CYAN}echo hello \$non_exist world${NC}\n"

# BASH
echo -e "  ${BLUE}BASH:${NC}"
bash -c 'echo hello $non_exist world'

# MINISHELL
echo -e "\n  ${BLUE}MINISHELL:${NC}"
echo 'echo hello $non_exist world' | $MINISHELL 2>&1 | grep -v "Token:" | grep -v "DEBUG:" | grep -v "^==" | sed '/LeakSanitizer/,/SUMMARY/d' | head -1

echo -e "\n  ${YELLOW}➜${NC} Debería imprimir ${GREEN}hello world${NC}, no solo ${RED}hello${NC}\n"
echo -e "${BLUE}─────────────────────────────────────────────────────────${NC}\n"

# ═══════════════════════════════════════════════════════════
#   RESUMEN
# ═══════════════════════════════════════════════════════════

echo -e "${BOLD}${BLUE}"
echo "═══════════════════════════════════════════════════════════"
echo "  RESUMEN DE BUGS VERIFICADOS"
echo "═══════════════════════════════════════════════════════════"
echo -e "${NC}\n"

echo -e "${RED}🔴 Bugs Críticos:${NC}"
echo -e "  1. Exit status = 0 en errores de sintaxis (debería ser 2)"
echo -e "  2. Wildcards (* y .*) no se expanden"
echo -e "  5. Variables inexistentes eliminan palabras siguientes"
echo ""
echo -e "${YELLOW}🟡 Bugs Medios:${NC}"
echo -e "  3. Sintaxis \${VAR} no soportada ${CYAN}(verificar subject)${NC}"
echo -e "  4. Variables con espacios no se colapsan (word splitting)"
echo ""
echo -e "${BLUE}📋 Siguiente paso:${NC}"
echo -e "  • Ver informe completo: ${CYAN}cat tester/INFORME_BUGS.md${NC}"
echo -e "  • Ejecutar tests: ${CYAN}cd tester/parsing_tests && ./run_all_tests.sh${NC}"
echo -e "  • Resumen ejecutivo: ${CYAN}cat tester/RESUMEN_EJECUTIVO.md${NC}"
echo ""
