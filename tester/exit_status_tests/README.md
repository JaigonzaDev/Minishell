# Exit Status Tests ($?)

Suite de pruebas para validar la correcta implementación de la variable `$?` (exit status del último comando) en minishell.

## Scripts Disponibles

### 1. test_manual.sh
Script principal que simula interacción humana con pruebas exhaustivas.

**Ejecutar:**
```bash
./test_manual.sh
```

**Cobertura:**
- Comandos básicos (true, false, pwd, echo)
- Builtins (cd, export, unset)
- Comandos externos (ls, cat, comandos inexistentes)
- Redirecciones (>, <)
- Pipes simples y múltiples
- Pipes con builtins
- Casos complejos

**Resultados esperados:** 30/30 tests OK (100%)

### 2. test_exit_status.sh
Script rápido de validación de exit status básicos.

**Ejecutar:**
```bash
./test_exit_status.sh
```

### 3. comparacion_final.sh
Script de comparación entre versión original y versión con fix del parser.

**Ejecutar:**
```bash
./comparacion_final.sh
```

## Cambios Implementados

### 1. source/commands/parse.c
**Problema:** El parser rechazaba tokens después de operadores de redirección (`>`, `<`) porque esperaba específicamente tipo `E_FILE`, pero los tokens venían con `type == 0`.

**Solución:** Modificar `correct_syntax()` para aceptar tokens sin tipo asignado:
```c
// Línea ~267
else if (is_word(current->type) || current->type == 0)
    state = E_STATE_EXPECT_ARG;
```

### 2. source/builtins/cd.c
**Problema:** `ft_cd()` era `void`, no propagaba exit status.

**Solución:** Cambiar a `int` y retornar valores apropiados:
- `return (0)` en caso de éxito
- `return (1)` en caso de error

### 3. source/builtins/builtins_utils.c
**Problema:** Llamaba `update_exit_status()` redundantemente.

**Solución:** Eliminar la llamada duplicada (se actualiza en `main.c`).

### 4. source/main.c
**Problema:** `update_exit_status()` nunca se llamaba después de ejecutar comandos.

**Solución:** Agregar `update_exit_status(status)` después de `bash_execute()`.

### 5. include/builtins.h
**Cambio:** Actualizar firma de `ft_cd` de `void` a `int`.

## Mejoras Logradas

| Métrica | Antes | Después | Mejora |
|---------|-------|---------|--------|
| Tests OK | 21/30 | 30/30 | +43% |
| Tasa de éxito | 70% | 100% | +30% |

## Tests que Ahora Pasan

✅ Redirecciones (`echo test > /dev/null`)  
✅ Exit status después de errores de parsing  
✅ Pipes múltiples (`true | true | false`)  
✅ Comandos que fallan (`cd /inexistente`, `cat /inexistente`)  
✅ Comandos inexistentes (exit 127)  
✅ Builtins con exit status correcto  

## Uso

Para ejecutar todos los tests y verificar que la implementación es correcta:

```bash
cd tester/exit_status_tests
chmod +x *.sh
./test_manual.sh
```

Si todos los tests pasan (30/30), la implementación de `$?` está completa y funcional.
