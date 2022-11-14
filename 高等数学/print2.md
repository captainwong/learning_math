
### 几个重要的等价关系

当 $x\rightarrow 0$ 时， **注意** $x$ 可以用 $f(x)$ 替换，只要 $f(x) \rightarrow 0$ 

1. $\sin x \sim x$

2. $\tan x \sim x$
   
   **证** 

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0}\frac{\tan x} x & = \lim\limits_{x\rightarrow 0}(\frac {\sin x} x \cdot \frac 1 {\cos x}) \\
   & = \lim\limits_{x\rightarrow 0}\frac{\sin x} x \cdot \lim\limits_{x\rightarrow 0}\frac 1{\cos x} \\
   & = 1 \\
   \therefore \tan x & \sim x
   \end{align}
   $$

3. $\arcsin x \sim x$
   
   **证**

   令 $x=\sin t$，即 $t=\arcsin x$，当 $x\rightarrow 0$ 时，有 $t\rightarrow 0$.于是由复合函数的极限运算法则得

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0}\frac{\arcsin x}x & = \lim\limits_{t\rightarrow 0}\frac{t}{\sin t} \\
   & = 1 \\
   \therefore \arcsin x & \sim x
   \end{align}
   $$


4. $\arctan x \sim x$
   
   **证** 
	
   令 $x=\tan t$，即 $t=\arctan x$，当 $x\rightarrow 0$ 时， $t\rightarrow 0$. 于是由复合函数的极限运算法则得

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0}\frac{\arctan x}{x} &= \lim\limits_{t\rightarrow 0} \frac{t}{\tan t} \\
   & = 1 \\
   \therefore \arctan x &\sim x
   \end{align}
   $$

5. $1-\cos x \sim \frac 1 2 x^2$

   **证**

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0} \frac{1-\cos x}{\frac 1 2 x^2} & = \lim\limits_{x\rightarrow 0}\frac{1-(1-2\sin^2{\frac x 2})}{\frac 1 2 x^2} \\
   & = \lim\limits_{x\rightarrow 0}\frac{2\sin^2{\frac x 2}}{\frac 4 2 (\frac x 2)^2} \\
   & = \lim\limits_{x\rightarrow 0}(\frac{\sin{\frac x 2}}{\frac x 2})^2 \\
   & = 1 \\
   \therefore 1-\cos x & \sim \frac 1 2 x^2
   \end{align}
   $$


6. $\sec x - 1 \sim \frac 1 2 x^2$
    
   **证**

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0}\frac{\sec x - 1}{x^2 / 2} & = \lim\limits_{x\rightarrow 0}(\frac{1-\cos^2x}{x^2 / 2} \cdot \frac 1 {\cos x}) \\
   & = \lim\limits_{x\rightarrow 0}(\frac{2\sin^2\frac x 2}{x^2/2} \cdot \frac 1 {\cos x}) \\
   & = \lim\limits_{x\rightarrow 0}\frac{\sin^2{\frac x 2}}{(\frac x 2)^2} \cdot \lim\limits_{x\rightarrow 0}\frac 1 {\cos x} \\
   & = 1 \\
   \therefore \sec x - 1 & \sim \frac{x^2}{2}
   \end{align}
   $$

7. $\sqrt[n]{1+x} - 1 \sim \frac x n$

   **证** 由于 [^1]

   $$
   \begin{align}
   & (a-1)(a^{n-1}+a^{n-2}+\cdots + a + 1) \\
   & = (a^n + a^{n-1} + \cdots + a) - (a^{n-1} + a^{n-2} + \cdots + a + 1) \\
   & = a^n - 1
   \end{align}
   $$

   以 $\sqrt[n]{1+x}$ 替换 $a$，有：

   $$
   (\sqrt[n]{1+x} - 1)(\sqrt[n]{(1+x)^{n-1}} + \sqrt[n]{(1+x)^{n-2}} + \cdots + 1) = (\sqrt[n]{(1+x)})^n-1
   $$

   从而

   $$
   \sqrt[n]{1+x} - 1 = \frac{(\sqrt[n]{(1+x)})^n-1}{\sqrt[n]{(1+x)^{n-1}} + \sqrt[n]{(1+x)^{n-2}} + \cdots + 1}
   $$

   那么

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0}\frac{\sqrt[n]{1+x} - 1}{\frac x n} & = \lim\limits_{x\rightarrow 0}\frac{(\sqrt[n]{(1+x)})^n-1}{\frac x n \sqrt[n]{(1+x)^{n-1}} + \sqrt[n]{(1+x)^{n-2}} + \cdots + 1}\\
   & = \lim\limits_{x\rightarrow 0}\frac n{\sqrt[n]{(1+x)^{n-1}} + \sqrt[n]{(1+x)^{n-2}} + \cdots + 1} \\
   & = 1
   \end{align}
   $$

   所以 $\sqrt[n]{1+x} - 1 \sim \frac x n(x \rightarrow 0)$. [^2]

8. $(1+x)^\alpha - 1 \sim \alpha x(\alpha \in \R)$ 这是关系7的拓展情形

9. $e^x - 1 \sim x$

   **证** [^3] 令 $t=e^x-1$，即 $x=\ln (1+t)$，当 $x\rightarrow 0$ 时， $t\rightarrow 0$，于是由复合函数的极限运算法则得

   $$
   \begin{align}
   \lim\limits_{x\rightarrow 0}\frac{e^x-1}{x} & =  \lim\limits_{t\rightarrow 0}\frac{t}{\ln(1+t)} \\
   & = \lim\limits_{t\rightarrow 0}\frac 1{\ln[(1+t)^{\frac 1 t}]} \\
   & = \frac 1{\ln[{\lim\limits_{t\rightarrow 0}(1+t)^{\frac 1 t}}]} \\
   & = \frac 1 {\ln e} \\
   & = 1 \\
   \therefore e^x - 1 & \sim x
   \end{align}
   $$

10. $a^x - 1 \sim x \ln a$

    **证** 令 $t=a^x-1$，即 $x=\log_a (1+t)$，当 $x\rightarrow 0$时， $t\rightarrow 0$，因此

    $$
    \begin{align}
    \lim\limits_{x\rightarrow 0}\frac{a^x-1}{x \cdot \ln a} & = \lim\limits_{t\rightarrow 0}\frac{t}{\log_a(1+t) \cdot \ln a} \\
    & = \lim\limits_{t\rightarrow 0}\frac{1}{\log_a(1+t)^{\frac 1 t} \cdot \ln a} \\
    & = \frac 1{\log_a(\lim\limits_{t\rightarrow 0}(1+t)^{\frac 1 t}) \cdot \ln a} \\
    & = \frac 1 {\log_a e \cdot \ln a} \\
    & = \frac 1 {\log_a e^{\ln a}} \\
    & = \frac 1{log_a a} \\
    & = \frac 1 1 \\
    & = 1 \\
    \therefore a^x -1 & \sim x\ln a
    \end{align}
    $$

11. $\ln(1+x) \sim x$
    
    **证**

    $$
    \begin{align}
    \lim\limits_{x\rightarrow 0}\frac{\ln(1+x)}x & = \lim\limits_{x\rightarrow 0}\ln(1+x)^{\frac1 x} \\
    & = \ln[\lim\limits_{x\rightarrow 0}(1+x)^{\frac 1 x}] \\
    & = \ln e \\
    & = 1 \\
    \therefore \ln(1+x) & \sim x
    \end{align}
    $$

