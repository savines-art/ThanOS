echo "[BITS 32]" > src/tramplins.asm
echo "[EXTERN collect_context]" >> src/tramplins.asm
echo "" >> src/tramplins.asm
for vector in {0..255}; do
  printf '[GLOBAL tramplin_0x%X]\n' "$vector" >> src/tramplins.asm
  printf 'tramplin_0x%X:\n' "$vector" >> src/tramplins.asm
  if (( !(vector == 8 || (vector >= 10 && vector <= 14) || vector == 17 || vector == 21) )); then
    echo "  push eax" >> src/tramplins.asm
  fi
  printf '  push 0x%X\n' "$vector" >> src/tramplins.asm
  echo "  jmp collect_context" >> src/tramplins.asm
  echo "" >> src/tramplins.asm
done