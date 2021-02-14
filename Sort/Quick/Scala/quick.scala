import scala.collection.mutable.ArrayBuffer

object Main{   

    def quickInterno(vet: ArrayBuffer[Int], inicio: Int, fim: Int): Unit = {

        if(fim-inicio > 0){
            var i = inicio
            var j = fim
            var pivot = vet((i+j)/2)

            do{
                while(vet(i) < pivot) i += 1
                while(vet(j) > pivot) j -= 1

                if(i <= j){
                    var temp = vet(i)
                    vet(i) = vet(j)
                    vet(j) = temp
                    i += 1
                    j -= 1
                }
            }while(i <= j)

            quickInterno(vet, inicio, j)
            quickInterno(vet, i, fim)
        }
    }

    def quickSort(vet: ArrayBuffer[Int]){
        quickInterno(vet, 0, vet.length-1)
    }

    def main(args: Array[String]): Unit = {

        //Exemplo
        val vet = ArrayBuffer(6,2,5,9,1,7,4,8,3)
        quickSort(vet)
        println(vet)
    }
}