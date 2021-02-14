import scala.collection.mutable.ArrayBuffer

object Main{

    def criaHeap(vet: ArrayBuffer[Int], inicio: Int, fim: Int): Unit = {

        var i = inicio
        val aux = vet(i)
        var j = i*2+1

        while(j <= fim){
            if(j < fim){
                if(vet(j) < vet(j+1)){
                    j += 1
                }
            }
            if(aux < vet(j)){
                vet(i) = vet(j)
                i = j
                j = 2*i+1
            }else{
                j = fim+1
            }
        }
        vet(i) = aux
        
    }

    def heapSort(vet: ArrayBuffer[Int]): Unit = {

        //cria heap a partir dos dados
        for(i <- (vet.length-1)/2 to 0 by -1){
            criaHeap(vet, i, vet.length-1)
        }

        var aux: Int = 0;
        //pegar o maior elemento da heap e colocar na sua posição correspondente no array
        for(i <- vet.length-1 to 1 by -1){
            aux = vet(0)
            vet(0) = vet(i)
            vet(i) = aux
            criaHeap(vet, 0, i-1)
        }
    }



    def main(args: Array[String]): Unit = {

        //Exemplo
        val vet = ArrayBuffer(6,1,9,4,8,2,5,7,3)
        heapSort(vet)
        println(vet)

    }
}