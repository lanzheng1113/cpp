class Something {
public:
  int m_nValue;
  Something(){ m_nValue = 0;}
  void ResetValue() {m_nValue = 0;}
  void SetValue(int nValue) {m_nValue = nValue;}
  int GetValue() {return m_nValue;}
}

int main() {
  const Something cSomething;
  cSomething.m_nValue = 5;
  cSomething.ResetValue();
  cSomething.SetValue(5);
  return 0;
}
