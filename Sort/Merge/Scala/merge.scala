import scala.collection.mutable.ArrayBuffer

object Main{

    def intercala(vet: ArrayBuffer[Int], aux: ArrayBuffer[Int], inicio: Int, fim: Int, meio: Int): Unit = {

        var ( i, k, j) = (inicio, inicio, meio+1)
        
        while((i <= meio) && (j <= fim)){

            if(vet(i) < vet(j)){
                aux(k) = vet(i)
                i += 1
            }else{
                aux(k) = vet(j)
                j += 1
            }
            k += 1
        }
        
        while(i <= meio){
            aux(k) = vet(i)
            i += 1
            k += 1
        }
        while(j <= fim){
            aux(k) = vet(j)
            j += 1
            k += 1
        }
        //Copía dados de volta para o vetor original
        for(k <- inicio to fim){
           
            vet(k) = aux(k)
        }

    }

    def mergeInterno(vet: ArrayBuffer[Int], aux: ArrayBuffer[Int], inicio: Int, fim: Int): Unit = {

        if(inicio < fim){
            var meio: Int = (inicio + fim)/2
            mergeInterno(vet, aux, inicio, meio)
            mergeInterno(vet, aux, meio+1, fim)
            intercala(vet, aux, inicio, fim, meio)
        }

    }

    def mergeSort(vet: ArrayBuffer[Int]): Unit = {
        
        val aux = ArrayBuffer[Int]()
        for(i <- 0 until vet.length) aux += 0
        mergeInterno(vet, aux, 0, vet.length-1) 

    }



    def main(args: Array[String]): Unit = {

        //Exemplo
        val vet = ArrayBuffer(5,3,7,8,2,6,1,9,4)
        mergeSort(vet)
        println(vet)

    }
}