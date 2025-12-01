# Resultados de Tests de Sintaxis

## Ejecución: $(date)

### Test 1: Mensajes de Error ✅
```bash
./test_syntax_manual.sh
```

**Resultado: 10/10 tests pasando** 🎉

Todos los errores de sintaxis son detectados correctamente con los mensajes apropiados.

### Test 2: Exit Code ($?) ❌
```bash
./test_syntax_exit_code.sh
```

**Resultado: 0/15 tests pasando** ⚠️

**Problema Identificado:**
- Los errores de sintaxis se detectan ✓
- Los mensajes de error son correctos ✓
- **PERO:** `$?` retorna 0 en lugar de 2 ✗

## Ejemplo del Problema

### Comportamiento Actual
```bash
minishell> ls >
minishell: syntax error near unexpected token 'newline'
minishell> echo $?
0        ← INCORRECTO: debería ser 2
```

### Comportamiento Esperado (bash)
```bash
bash$ ls >
bash: syntax error near unexpected token 'newline'
bash$ echo $?
2        ← CORRECTO
```

## Solución Necesaria

Cuando se detecta un error de sintaxis en `parse_commands_new()`:
1. Mostrar el mensaje de error ✅ (ya funciona)
2. **Actualizar `g_last_exit_status` a 2** ⚠️ (falta implementar)
3. No ejecutar el comando ✅ (ya funciona)

## Archivos Involucrados

- `source/commands/parse.c` - Detecta errores de sintaxis
- `source/builtins/builtins_utils.c` - Función `update_exit_status()`
- `source/main.c` - Loop principal que debe capturar el error

