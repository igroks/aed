import scala.collection.mutable.ArrayBuffer

object Main{

    val tamDoBalde = 5 // Tamanho dos Baldes

    //Para ordenar cada bucket usaremos o algoritmo Insertion Sort 
    //outra forma seria usar uma chamada recursiva.
    def insertionSort(vet: ArrayBuffer[Int]): Unit = {

        for(j <- 0 until vet.length){

            var pivot = vet(j)
            var i = j-1

            while((i >= 0) && (vet(i) > pivot)){
                vet(i+1) = vet(i)
                i -= 1;
            }
            vet(i+1) = pivot
        }
    }

    def bucketSort(vet: ArrayBuffer[Int]): Unit = {

        var (maior, menor) = (vet(0),vet(0))
        
        //Acha maior e menor valor
        for(elem <- vet){
            if(elem > maior){
                maior = elem
            }
            if(elem < menor){
                menor = elem
            }
        }
        
        //Inicializa Baldes
        val numBaldes = (maior-menor)/tamDoBalde+1
        val buckets = ArrayBuffer[ArrayBuffer[Int]]()
        for(i <- 0 until numBaldes) buckets += new ArrayBuffer[Int]

        //Distribui os valores nos baldes
        var pos = 0 
        for(elem <- vet){
            pos = (elem-menor)/tamDoBalde
            buckets(pos) += elem
        }

        //Ordena baldes e coloca no array original
        pos = 0
        for(bucket <- buckets){
            insertionSort(bucket)
            for(elem <- bucket){
                vet(pos) = elem
                pos += 1 
            }
        }
        
        
    }

    def main(args: Array[String]): Unit = {
        
        //Exemplo
        val vet = ArrayBuffer(4,9,6,2,7,3,8,5,1)
        bucketSort(vet)
        println(vet)
    }
}