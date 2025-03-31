from qiskit import QuantumCircuit, Aer, transpile, assemble, execute

def quantum_full_adder():
    # 5개의 양자비트와 2개의 고전비트를 가진 양자회로 생성
    qc = QuantumCircuit(5, 2)  # a, b, carry_in, auxiliary, carry_out
    
    # 입력 비트 할당:
    # q[0] = a (첫 번째 입력)
    # q[1] = b (두 번째 입력)
    # q[2] = carry_in (이전 자리에서의 올림수)
    
    # 출력 비트 할당:
    # q[3] = sum (합계 비트)
    # q[4] = carry_out (다음 자리로의 올림수)
    
    # Step 1: Compute sum bit using CNOT gates
    qc.cx(0, 3)  # Sum intermediate (XOR a with b)
    qc.cx(1, 3)  # Sum intermediate (XOR result with carry_in)
    qc.cx(2, 3)  # Final Sum (a ⊕ b ⊕ carry_in)
    
    
    # Step 2: Compute carry-out using Toffoli gates
    qc.ccx(0, 1, 4)  # a AND b -> carry_out
    qc.ccx(2, 3, 4)  # (a ⊕ b) AND carry_in -> carry_out
    
    # Measure sum and carry_out
    qc.measure(3, 0)  # sum -> classical bit 0
    qc.measure(4, 1)  # carry_out -> classical bit 1
    
    return qc

# Create and visualize the quantum full adder circuit
qc = quantum_full_adder()
qc.draw('mpl')
