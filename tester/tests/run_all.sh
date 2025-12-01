#!/bin/bash

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Directorio del minishell
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MINISHELL_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
MINISHELL="$MINISHELL_DIR/bin/minishell"

# Verificar que minishell existe
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}❌ Error: No se encuentra el ejecutable minishell en $MINISHELL${NC}"
    echo -e "${YELLOW}Por favor, compila el proyecto primero con 'make'${NC}"
    exit 1
fi

cd "$SCRIPT_DIR"

echo -e "${BLUE}╔════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║          MINISHELL - SUITE COMPLETA DE TESTS              ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════════╝${NC}"
echo ""

echo -e "${BLUE}┌────────────────────────────────────────────────────────────┐${NC}"
echo -e "${BLUE}│  TESTS OBLIGATORIOS                                        │${NC}"
echo -e "${BLUE}└────────────────────────────────────────────────────────────┘${NC}"
echo ""

# Variables para contar
total_failed=0

# 1. Exit codes de sintaxis
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo -e "${YELLOW}▶ 1. EXIT CODES DE SINTAXIS${NC}"
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo ""
./test_syntax_exit_code.sh
exit_code1=$?
[ $exit_code1 -ne 0 ] && total_failed=$((total_failed + 1))
echo ""

# 2. Mensajes de sintaxis
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo -e "${YELLOW}▶ 2. MENSAJES DE SINTAXIS${NC}"
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo ""
./test_syntax_manual.sh
exit_code2=$?
[ $exit_code2 -ne 0 ] && total_failed=$((total_failed + 1))
echo ""

# 3. Expansión de variables
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo -e "${YELLOW}▶ 3. EXPANSIÓN DE VARIABLES${NC}"
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo ""
./test_expander.sh
exit_code3=$?
[ $exit_code3 -ne 0 ] && total_failed=$((total_failed + 1))
echo ""

# 4. Redirecciones
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo -e "${YELLOW}▶ 4. REDIRECCIONES Y PIPES${NC}"
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo ""
./test_redirections.sh
exit_code4=$?
[ $exit_code4 -ne 0 ] && total_failed=$((total_failed + 1))
echo ""

# Tests bonus
echo -e "${BLUE}┌────────────────────────────────────────────────────────────┐${NC}"
echo -e "${BLUE}│  TESTS BONUS (OPCIONAL - NO OBLIGATORIO)                  │${NC}"
echo -e "${BLUE}└────────────────────────────────────────────────────────────┘${NC}"
echo ""

echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo -e "${YELLOW}▶ 5. WILDCARDS (*, ?, [...]) - BONUS${NC}"
echo -e "${YELLOW}═══════════════════════════════════════════════════════════${NC}"
echo ""
./test_wildcards.sh
echo ""

# Resumen final
echo -e "${BLUE}╔════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║                  RESUMEN GLOBAL                            ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════════╝${NC}"
echo ""

if [ $total_failed -eq 0 ]; then
    echo -e "${GREEN}✅ TODOS LOS TESTS OBLIGATORIOS PASARON (100%)${NC}"
    echo ""
    echo -e "${YELLOW}⚠️  Nota: Los tests de wildcards son OPCIONALES y no afectan la nota${NC}"
    exit 0
else
    echo -e "${RED}❌ $total_failed grupo(s) de tests fallaron${NC}"
    echo -e "${YELLOW}⚠️  Revisa los detalles arriba${NC}"
    exit 1
fi
